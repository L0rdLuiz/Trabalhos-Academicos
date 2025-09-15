import sys
import struct
import socket

def read_pgm_p5(path):
    with open(path, "rb") as f:
        magic = f.readline().strip()
        if magic != b'P5':
            raise ValueError("Somente PGM P5 (binário) suportado")
        def read_non_comment():
            line = f.readline()
            while line.startswith(b'#'):
                line = f.readline()
            return line
        dims = b""
        while True:
            line = read_non_comment()
            dims += line
            if len(dims.split()) >= 2:
                break
        parts = dims.split()
        w = int(parts[0]); h = int(parts[1])
        maxv_line = read_non_comment()
        maxv = int(maxv_line.split()[0])
        pixels = f.read(w*h)
        return w, h, maxv, pixels

def main():
    if len(sys.argv) != 4:
        print("Uso: python sender_socket.py <host> <porta> <entrada.pgm>")
        sys.exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])
    inpath = sys.argv[3]

    w,h,maxv,pixels = read_pgm_p5(inpath)
    header = struct.pack('<iii', w, h, maxv)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    sock.sendall(header)
    sock.sendall(pixels)
    sock.close()
    print(f"[sender] Enviado {w}x{h} pixels para {host}:{port}")

if __name__ == "__main__":
    main()
