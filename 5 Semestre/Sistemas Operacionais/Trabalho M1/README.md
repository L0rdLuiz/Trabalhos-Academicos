Autores

Luiz Antonio Haenisch
Isabela Silverio Cardoso Pereira

Estrutura dos Arquivos
sender.py: O programa responsável por ler uma imagem binária PGM (formato P5) e enviar seus metadados (dimensões, valor máximo de cor) e pixels.
worker.py: O programa que lê a imagem e a processa em paralelo. Ele usa um pool de threads para distribuir o trabalho de processamento de pixels, aplicando um filtro "negativo" ou "slice".

Para a Utilização do Código é necessário possuir Python em sua Máquina
Para aplicar o filtro negativo em uma imagem chamada entrada.pgm, usando 8 threads:

Terminal 1 (Worker):

./worker.py /tmp/imgpipe saida_neg.pgm neg 8
Terminal 2 (Sender):

./sender.py /tmp/imgpipe entrada.pgm
