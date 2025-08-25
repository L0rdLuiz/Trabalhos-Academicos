package com.mycompany.jogodavelha;

public class Main {
    public static void main(String[] args) {
        Jogar jogo = new Jogar(); // Instancia a classe Jogar
        Mostrartabuleiro mostrar = new Mostrartabuleiro(); // Instancia a classe para mostrar o tabuleiro

        for (int jogada = 0; jogada < 9; jogada++) {
            // Jogada do usuário
            jogo.usuarioJoga();
            mostrar.mostrarTabuleiro(jogo.getMatriz()); // Mostra o tabuleiro

            // Calcula os pesos e verifica se há vencedor
            int[] pesos = jogo.calculaOsPesos(); // Calcula os pesos da matriz
            int resultado = jogo.verificaSeTemVitoria(pesos); // Passa os pesos para verificar se há vitória
            if (resultado == 3) {
                System.out.println("Você (X) ganhou!");
                break;
            }

            if (jogada == 8) { // Se já foram feitas 9 jogadas e não há vencedor, é empate
                System.out.println("Empate!");
                break;
            }

            // Jogada do computador
            jogo.computadorJoga(); // Implementação da jogada do computador
            mostrar.mostrarTabuleiro(jogo.getMatriz()); // Mostra o tabuleiro novamente

            // Calcula os pesos e verifica se há vencedor após a jogada do computador
            pesos = jogo.calculaOsPesos(); // Recalcula os pesos
            resultado = jogo.verificaSeTemVitoria(pesos); // Verifica novamente
            if (resultado == 1) {
                System.out.println("Computador (O) ganhou!");
                break;
            }
        }
    }
}