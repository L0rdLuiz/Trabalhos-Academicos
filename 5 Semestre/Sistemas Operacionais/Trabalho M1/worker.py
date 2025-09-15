import sys, struct, socket, threading
from threading import Semaphore, Lock, Thread
import time

QMAX = 128

class CircularQueue:
    def __init__(self, capacity=QMAX):
        self.buf = [None]*capacity
        self.cap = capacity
        self.head = 0
        self.tail = 0
        self.count = 0
        self.lock = Lock()
        self.sem_items = Semaphore(0)
        self.sem_space = Semaphore(capacity)
    def put(self, item):
        self.sem_space.acquire()
        with self.lock:
            self.buf[self.tail] = item
            self.tail = (self.tail+1) % self.cap
            self.count += 1
        self.sem_items.release()
    def get(self):
        self.sem_items.acquire()
        with self.lock:
            item = self.buf[self.head]
            self.head = (self.head+1) % self.cap
            self.count -= 1
        self.sem_space.release()
        return item

def write_pgm_p5(path, w, h, maxv, pixels_bytes):
    with open(path, "wb") as f:
        f.write(b"P5\n")
        f.write(f"{w} {h}\n".encode())
        f.write(f"{maxv}\n".encode())
        f.write(pixels_bytes)

def apply_negative_block(in_bytes, out_array, w, rs, re):
    for r in range(rs, re):
        off = r*w
        for c in range(w):
            out_array[off+c] = 255 - in_bytes[off+c]

def apply_slice_block(in_bytes, out_array, w, rs, re, t1, t2):
    for r in range(rs, re):
        off = r*w
        for c in range(w):
            val = in_bytes[off+c]
            if val <= t1 or val >= t2:
                out_array[off+c] = 255
            else:
                out_array[off+c] = val

def worker_thread_fn(queue, in_bytes, out_array, w, mode, t1, t2, counter, lock, cond):
    while True:
        task = queue.get()
        if task is None:
            break
        rs,re = task
        if mode=="neg":
            apply_negative_block(in_bytes,out_array,w,rs,re)
        else:
            apply_slice_block(in_bytes,out_array,w,rs,re,t1,t2)
        with lock:
            counter[0] -= 1
            if counter[0] == 0:
                cond.notify_all()

def main():
    start = time.perf_counter()
    if len(sys.argv)<5:
        print("Uso: python worker_socket.py <porta> <saida.pgm> <neg|slice> [t1 t2] [nthreads]")
        sys.exit(1)
    port = int(sys.argv[1])
    outpath = sys.argv[2]
    mode = sys.argv[3]
    idx = 4
    if mode=="slice":
        t1=int(sys.argv[4]); t2=int(sys.argv[5]); idx=6
    else:
        t1=t2=0
    nthreads = int(sys.argv[idx]) if len(sys.argv)>idx else 4

    # socket servidor
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("localhost", port))
    sock.listen(1)
    print(f"[worker] Esperando conexão na porta {port}...")
    conn, addr = sock.accept()
    print(f"[worker] Conectado de {addr}")

    # receber header
    hdr = conn.recv(12)
    w,h,maxv = struct.unpack('<iii', hdr)
    print(f"[worker] Recebido header: {w}x{h}, maxv={maxv}")
    pixels = bytearray()
    while len(pixels) < w*h:
        chunk = conn.recv(w*h - len(pixels))
        if not chunk: break
        pixels.extend(chunk)
    conn.close(); sock.close()

    in_bytes = pixels
    out_array = bytearray(w*h)

    q = CircularQueue(QMAX)
    total_tasks = h
    counter=[total_tasks]
    lock = Lock()
    cond = threading.Condition(lock)

    threads=[]
    for i in range(nthreads):
        t=Thread(target=worker_thread_fn,args=(q,in_bytes,out_array,w,mode,t1,t2,counter,lock,cond))
        t.start(); threads.append(t)

    for r in range(h):
        q.put((r,r+1))

    with cond:
        while counter[0]>0:
            cond.wait()

    for _ in range(nthreads): q.put(None)
    for t in threads: t.join()

    write_pgm_p5(outpath,w,h,maxv,bytes(out_array))
    print(f"[worker] Imagem salva em {outpath}")
    end = time.perf_counter()
    print(f"Tempo total de execução: {end - start:.3f} segundos")

if __name__=="__main__":
    main()
