package com.mycompany.jogodavelha;

import java.util.Random;
import java.util.Scanner;

public class Jogar {
    
    private int[][] matriz;
    private Conversor conversor;
    private Scanner scanner;

    public Jogar() {
        matriz = new int[3][3];
        conversor = new Conversor();
        scanner = new Scanner(System.in);
        inicializarTabuleiro();
    }

    public int[][] getMatriz() {
        return matriz;
    }

    private void inicializarTabuleiro() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matriz[i][j] = 0;
            }
        }
    }

    public int verificaSeXGanhou(int[] pesos) {
        for (int peso : pesos) {
            if (peso == 27) {
                return 3; // X ganhou
            }
        }
        return 2; // O jogo continua
    }

    public int verificaSeOGanhou(int[] pesos) {
        for (int peso : pesos) {
            if (peso == 1) {
                return 1; // O ganhou
            }
        }
        return 2; // O jogo continua
    }

    public int verificaSeTemVitoria(int[] pesos) {
        int resultadoX = verificaSeXGanhou(pesos);
        if (resultadoX == 3) {
            return 3; // X ganhou
        }

        int resultadoO = verificaSeOGanhou(pesos);
        if (resultadoO == 1) {
            return 1; // O ganhou
        }

        return 2; // Ninguém ganhou
    }

    public int[] calculaOsPesos() {
        int[] pesos = new int[8]; // 3 linhas, 3 colunas, 2 diagonais

        // Calcula o produto das linhas
        for (int i = 0; i < 3; i++) {
            pesos[i] = matriz[i][0] * matriz[i][1] * matriz[i][2];
        }

        // Calcula o produto das colunas
        for (int i = 0; i < 3; i++) {
            pesos[i + 3] = matriz[0][i] * matriz[1][i] * matriz[2][i];
        }

        // Calcula o produto das diagonais
        pesos[6] = matriz[0][0] * matriz[1][1] * matriz[2][2]; // Diagonal principal
        pesos[7] = matriz[0][2] * matriz[1][1] * matriz[2][0]; // Diagonal secundária

        return pesos;
    }

    public int verificaSeAPosicaoEstaLivre(int linha, int coluna) {
        if (matriz[linha][coluna] == 0) { // Verifica se o valor é 0 (livre)
            return 1; // A posição está livre
        }
        return 0; // A posição está ocupada
    }

    public void usuarioJoga() {
        int linha, coluna;
        do {
            System.out.println("Sua vez! Escolha a linha e coluna (0, 1 ou 2):");
            linha = scanner.nextInt();
            coluna = scanner.nextInt();
        } while (verificaSeAPosicaoEstaLivre(linha, coluna) == 0);
        
        matriz[linha][coluna] = 3; // X joga
    }

    public void computadorJoga() {
        int[] pesos = calculaOsPesos(); // Calcula os pesos antes de tomar a decisão
        int alerta = verSeEstouEmAlerta(pesos);

        if (alerta == 1) { // Alerta: jogador X está perto de ganhar (peso 18)
            // Tentar bloquear o jogador
            for (int i = 0; i < pesos.length; i++) {
                if (pesos[i] == 18) { // X está perto de ganhar, então bloquear
                    if (i < 3) { // Índice para linhas (0, 1, 2)
                        for (int j = 0; j < 3; j++) {
                            if (matriz[i][j] == 0) { // Encontra a célula vazia na linha
                                matriz[i][j] = 1; // O joga para bloquear
                                return;
                            }
                        }
                    } else if (i < 6) { // Índice para colunas (3, 4, 5)
                        int coluna = i - 3;
                        for (int k = 0; k < 3; k++) {
                            if (matriz[k][coluna] == 0) { // Encontra a célula vazia na coluna
                                matriz[k][coluna] = 1; // O joga para bloquear
                                return;
                            }
                        }
                    } else if (i == 6) { // Diagonal principal
                        for (int l = 0; l < 3; l++) {
                            if (matriz[l][l] == 0) { // Encontra a célula vazia na diagonal principal
                                matriz[l][l] = 1; // O joga para bloquear
                                return;
                            }
                        }
                    } else if (i == 7) { // Diagonal secundária
                        for (int m = 0; m < 3; m++) {
                            if (matriz[m][2 - m] == 0) { // Encontra a célula vazia na diagonal secundária
                                matriz[m][2 - m] = 1; // O joga para bloquear
                                return;
                            }
                        }
                    }
                }
            }
        } else { // Se não estiver em alerta, jogar na célula com maior peso
            Random random = new Random();
            int linha, coluna;

            // Seleciona uma célula aleatória que está livre
            do {
                linha = random.nextInt(3); // Gera um número aleatório entre 0 e 2
                coluna = random.nextInt(3); // Gera um número aleatório entre 0 e 2
            } while (matriz[linha][coluna] != 0); // Repete até encontrar uma célula vazia

            matriz[linha][coluna] = 1; // O joga
        }
    }
    
    public int verSeEstouEmAlerta(int [] pesos) {
       for (int peso : pesos) {
           if (peso == 18) {
               return 1; //estou para perder
           }
           if (peso == 2) {// estou para ganhar
               return 2;
           }
       }
       return 0;
    }

}