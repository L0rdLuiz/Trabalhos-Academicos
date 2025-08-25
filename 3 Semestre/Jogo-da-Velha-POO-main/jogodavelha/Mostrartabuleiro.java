package com.mycompany.jogodavelha;

public class Mostrartabuleiro {
    private Conversor conversor;

    public Mostrartabuleiro() {
        this.conversor = new Conversor();
    }

    public void mostrarTabuleiro(int matriz[][]) {
        System.out.println(conversor.converter(matriz[0][0]) + " | " + conversor.converter(matriz[0][1]) + " | " + conversor.converter(matriz[0][2]));
        System.out.println("--|---|---");
        System.out.println(conversor.converter(matriz[1][0]) + " | " + conversor.converter(matriz[1][1]) + " | " + conversor.converter(matriz[1][2]));
        System.out.println("--|---|---");
        System.out.println(conversor.converter(matriz[2][0]) + " | " + conversor.converter(matriz[2][1]) + " | " + conversor.converter(matriz[2][2]));
    }
}