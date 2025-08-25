package com.mycompany.jogodavelha;

public class Conversor
{
    public char converter(int numero){
        char letra;
        switch(numero){
            case 1: letra = 'O'; break;
            case 3: letra = 'X'; break;
            default: letra = ' '; break;
        }
        return letra;
    }


}
