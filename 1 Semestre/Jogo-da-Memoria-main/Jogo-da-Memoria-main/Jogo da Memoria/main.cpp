#include <iostream>
#include <locale.h>
using namespace std;
//para o rand
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//para formar o vetor da matriz principal
#include <algorithm>
#include <vector>

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "portuguese");

    //Variaveis
    const int tamanho = 4;
    const int numerosTotais = tamanho * tamanho;
    int matrizP[tamanho][tamanho];
    int matrizG [4][4];
    int matrizJ [4][4];
    int modoJogo;
    int resposta = 0;
    int tentativas = 0;
    int selLinha1;
    int selColuna1;
    int selLinha2;
    int selColuna2;


    //Fazer a matriz Principal

    //Forma o vetor
    int numeros[numerosTotais];
    for (int i = 0; i < numerosTotais; ++i) {
        numeros[i] = i % (numerosTotais / 2) + 1;
    }

    //Aleatorizar a ordem dos números
    random_shuffle(begin(numeros), end(numeros));

    //Index serve para selecionar a casa do vetor e aqui forma a matriz principal
    int index = 0;
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            matrizP[i][j] = numeros[index++];
        }
    }

    //Modos de jogo

    modoJogo = rand() %4+1;

    switch(modoJogo) {
        case 1: //Matriz Gabarito igual a principal;
            for(int lp=0; lp<4; lp++){
                for (int cp=0; cp<4; cp++) {
                    matrizG[lp][cp] = matrizP[lp][cp];
                    matrizJ[lp][cp] = 0;
                }
            }

        break;
        case 2: //Matriz Transposta

            //Matriz Gabarito e Matriz Jogo
            for(int lp=0; lp<4; lp++){
                for (int cp=0; cp<4; cp++) {
                    matrizG[lp][cp] = matrizP[cp][lp];
                    matrizJ[lp][cp] = 0;
                }
            }

        break;
        case 3: //Matriz Invertida por linha
            for(int lp=3; lp>=0; lp--){
                for (int cp=0; cp<4; cp++) {
                    matrizG[lp][cp] = matrizP[lp][cp];
                    matrizJ[lp][cp] = 0;
                }
            }

        break;
        case 4:
            for(int lp=0; lp<4; lp++){
                for (int cp=3; cp>=0; cp--) {
                    matrizG[lp][cp] = matrizP[lp][cp];
                    matrizJ[lp][cp] = 0;
                }
            }

        break;
    }

    //Jogo
    while (resposta<8 && tentativas <= 24) {

        //mostra a matriz jogo
        for (int i = 0; i<4; i++) {
            for (int j=0; j<4; j++) {
                cout<<matrizJ[i][j]<<" ";
            }
            cout<<"\n";
        }

        cout<<"\n\nVocê fez "<<tentativas<<" Jogada(s).";

        do {
            cout<<endl<<"Escreva a linha de 1 a 4 que você quer escolher."<<endl;
            cin>>selLinha1;

            //Verifica se está digitando um número de 1 a 4
            while (selLinha1 < 1 || selLinha1 > 4) {
                cout << "Valor inválido. Por favor, insira um valor entre 1 e 4." << endl;
                cin >> selLinha1;
            }

            cout<<endl<<"Escreva a coluna de 1 a 4 que você quer escolher."<<endl;
            cin>>selColuna1;

            //Verifica se está digitando um número de 1 a 4
            while (selColuna1 < 1 || selColuna1 > 4) {
                cout << "Valor inválido. Por favor, insira um valor entre 1 e 4." << endl;
                cin >> selColuna1;
            }

            selLinha1 = selLinha1-1;
            selColuna1 = selColuna1-1;

            if(matrizJ[selLinha1][selColuna1] != 0) {
                cout<<"Esta casa já foi selecionada.\n";
            }

        }while(matrizJ[selLinha1][selColuna1] != 0);

            //Selecionar primeiro Número
            for (int lp1=0; lp1<4; lp1++) {
                for (int cp1=0; cp1<4; cp1++) {
                    if (selLinha1 == lp1 && selColuna1 == cp1) {
                        matrizJ[lp1][cp1] = matrizG[lp1][cp1];
                        cout<<matrizJ[lp1][cp1]<<" ";
                    } else {
                        cout<<matrizJ[lp1][cp1]<<" ";
                    }
                }
                cout<<endl;
            }

            do {
                cout<<endl<<"Escreva a linha de 1 a 4 que você quer escolher."<<endl;
                cin>>selLinha2;

                //Verifica se está digitando um número de 1 a 4
                while (selLinha2 < 1 || selLinha2 > 4) {
                    cout << "Valor inválido. Por favor, insira um valor entre 1 e 4." << endl;
                    cin >> selLinha2;
                }

                cout<<endl<<"Escreva a coluna de 1 a 4 que você quer escolher."<<endl;
                cin>>selColuna2;

                //Verifica se está digitando um número de 1 a 4
                while (selColuna2 < 1 || selColuna2 > 4) {
                    cout << "Valor inválido. Por favor, insira um valor entre 1 e 4." << endl;
                    cin >> selColuna2;
                }

                selLinha2 = selLinha2-1;
                selColuna2 = selColuna2-1;

                if(matrizJ[selLinha2][selColuna2] != 0) {
                    cout<<"Esta casa já foi selecionada.\n";
                }

            }while(matrizJ[selLinha2][selColuna2] != 0);

            //Selecionar Segundo Número
            for (int lp2=0; lp2<4; lp2++) {
                for (int cp2=0; cp2<4; cp2++) {
                    if (selLinha2 == lp2 && selColuna2 == cp2) {
                        matrizJ[lp2][cp2] = matrizG[lp2][cp2];
                        cout<<matrizJ[lp2][cp2]<<" ";
                    } else {
                        cout<<matrizJ[lp2][cp2]<<" ";
                    }
                }
                cout<<endl;
            }

            //Verifica se os números são iguais e da certo
            if (matrizJ[selLinha1][selColuna1] == matrizJ[selLinha2][selColuna2]) {
                for (int lp = 0; lp<4; lp++){
                    for (int cp = 0; cp<4; cp++) {
                        matrizJ[selLinha1][selColuna1] = matrizG[selLinha1][selColuna1];
                        matrizJ[selLinha2][selColuna2] = matrizG[selLinha2][selColuna2];
                    }
                }
                cout<<endl<<"JOGADA OK"<<endl;
                resposta++;
                tentativas++;
                system("pause");
                system("cls");
            }

            //Verifica se os numeros são iguais e da errado
            else {
                for (int lp = 0; lp<4; lp++){
                    for (int cp = 0; cp<4; cp++) {
                        matrizJ[selLinha1][selColuna1] = 0;
                        matrizJ[selLinha2][selColuna2] = 0;
                    }
                }
                tentativas++;
                cout<<endl<<"JOGADA NOK"<<endl;
                system("pause");
                system("cls");
            }
    }

    if (resposta == 8) {
        cout<<"Parabéns você concluiu o jogo e conseguiu um cookie.";
    } else {
        cout<<"Infelizmente você perdeu todas tentativas mas acertou " << resposta<<" boa sorte na próxima!"<<endl;
    }

    cout<<"\n\nJogo criado por:\n";
    cout<<"Luiz Antonio Haenisch\n";
    cout<<"Daniel Machado Nascimento\n";
    cout<<"Vitoria Araujo\n";
}
