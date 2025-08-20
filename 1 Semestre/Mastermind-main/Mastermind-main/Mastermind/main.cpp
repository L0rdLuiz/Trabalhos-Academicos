#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    //Variáveis
    int menu;
    int dificuldade;
    int n1,n2,n3,n4, n5;
    int tent = 1;
    int res1, res2, res3, res4, res5;
    int posiCer;
    int posiErr;

    do {
        system("cls");
        cout<<"Mastermind: A senha\n\n";
        cout<<"Jogar (1)\n";
        cout<<"Dificuldade (2)\n";
        cout<<"Sobre (3)\n";
        cout<<"Regras (4) \n";
        cout<<"Fim (5) Finaliza o jogo\n";
        cin>>menu;

        switch (menu) {
            case 1:
                cout<<"Jogo\n";
                system("cls");

                do{
                    srand (time(NULL));
                    n1 = rand() % 5 + 1;

                    n2 = rand() % 5 + 1;

                    n3= rand() % 5 + 1;

                    n4= rand() % 5 + 1;

                    n5= rand() % 5 + 1;

                }while( n1 == n2 || n1 == n3 || n1 == n4 || n2 == n3 || n2 == n4 || n3 == n4 || n1 == n5 || n2 == n5 || n3 == n5 || n4 == n5);

                switch (dificuldade) {
                    case 1:
                        cout<<"Modo Fácil\n";
                        while (tent < 9 || posiCer == 3){
                            cout<<"Digite 3 números de 1 a 6\n\n";
                            do {
                                cin>>res1;
                                cin>>res2;
                                cin>>res3;
                            } while (res1 < 1 || res1 > 6 || res2 < 1 || res2 > 6 || res3 < 1 || res3 > 6);

                            posiCer = 0;
                            posiErr = 0;

                            //Verifica se acertou números em posições corretas
                            if (res1 == n1) {
                                posiCer = posiCer+1;
                            }else if (res1 == n2 || res1 == n3) {
                                posiErr = posiErr+1;
                            }

                            if (res2 == n2) {
                                posiCer = posiCer+1;
                            }else if (res2 == n1 || res2 == n3) {
                                posiErr = posiErr+1;
                            }

                            if (res3 == n3) {
                                posiCer = posiCer+1;
                            }else if (res3 == n2 || res3 == n1) {
                                posiErr = posiErr+1;
                            }

                            //Pega o verificador e mostra o resultado na tela
                            if (posiCer == 3) {
                                cout<<"Você acertou parabéns\n\n";
                                system("pause");
                                break;
                            }

                            if (posiCer != 3 || posiCer != 0) {
                                cout<<"Você acertou tantos "<< posiErr << " números em posições erradas.\n";
                                cout<<"Você acertou tantos "<< posiCer << " números em posições corretas.\n";
                                cout<<"Você tem mais "<< 8-tent << " tentativas.\n\n";
                            }

                            if (posiErr == 0 && posiCer == 0) {
                                cout<<"Você não acertou nada";
                            }

                            tent++;

                            //Mostra que perdeu
                            if (tent == 9) {
                                cout<<"Você perdeu acabou suas tentativas\n";
                                system("pause");
                            }
                        }
                        tent = 0;
                        posiCer = 0;
                        break;
                    case 2:
                        cout<<"Medio\n\n";
                        while (tent < 11 || posiCer == 4){
                            cout<<"Digite 4 números de 1 a 6\n\n";
                            do {
                                cin>>res1;
                                cin>>res2;
                                cin>>res3;
                                cin>>res4;
                            } while (res1 < 1 || res1 > 6 || res2 < 1 || res2 > 6 || res3 < 1 || res3 > 6 || res4 < 1 || res4 > 6);

                            posiCer = 0;
                            posiErr = 0;

                            //Verifica se acertou números em posições corretas
                            if (res1 == n1) {
                                posiCer = posiCer+1;
                            }else if (res1 == n2 || res1 == n3 || res1 == n4) {
                                posiErr = posiErr+1;
                            }

                            if (res2 == n2) {
                                posiCer = posiCer+1;
                            }else if (res2 == n1 || res2 == n3 || res2 == n4) {
                                posiErr = posiErr+1;
                            }

                            if (res3 == n3) {
                                posiCer = posiCer+1;
                            }else if (res3 == n2 || res3 == n1 || res3 == n3) {
                                posiErr = posiErr+1;
                            }

                            if (res4 == n4) {
                                posiCer = posiCer+1;
                            }else if (res4 == n2 || res4 == n1 || res4 == n3) {
                                posiErr = posiErr+1;
                            }

                            //Pega o verificador e mostra o resultado na tela
                            if (posiCer == 4) {
                                cout<<"Você acertou parabéns\n\n";
                                system("pause");
                                break;
                            }

                            if (posiCer != 4 || posiCer != 0) {
                                cout<<"Você acertou tantos "<< posiErr << " números em posições erradas.\n";
                                cout<<"Você acertou tantos "<< posiCer << " números em posições corretas.\n";
                                cout<<"Você tem mais "<< 10-tent << " tentativas.\n\n";
                            }

                            if (posiErr == 0 && posiCer == 0) {
                                cout<<"Você não acertou nada";
                            }

                            tent++;
                            //Mostra que perdeu
                            if (tent == 11) {
                                cout<<"Você perdeu acabou suas tentativas\n";
                                system("pause");
                            }
                        }
                        tent = 0;
                        posiCer = 0;
                        break;
                    case 3:
                        cout<<"Dificil\n\n";
                        while (tent < 13 || posiCer == 5){
                            cout<<"Digite 5 números de 1 a 6\n\n";
                            do {
                                cin>>res1;
                                cin>>res2;
                                cin>>res3;
                                cin>>res4;
                                cin>>res5;
                            } while (res1 < 1 || res1 > 6 || res2 < 1 || res2 > 6 || res3 < 1 || res3 > 6 || res4 < 1 || res4 > 6 || res5 < 1 || res5 > 6);

                            posiCer = 0;
                            posiErr = 0;

                            //Verifica se acertou números em posições corretas
                            if (res1 == n1) {
                                posiCer = posiCer+1;
                            }else if (res1 == n2 || res1 == n3 || res1 == n4 || res1 == n5) {
                                posiErr = posiErr+1;
                            }

                            if (res2 == n2) {
                                posiCer = posiCer+1;
                            }else if (res2 == n1 || res2 == n3 || res2 == n4 || res2 == n5) {
                                posiErr = posiErr+1;
                            }

                            if (res3 == n3) {
                                posiCer = posiCer+1;
                            }else if (res3 == n2 || res3 == n1 || res3 == n4 || res3 == n5) {
                                posiErr = posiErr+1;
                            }

                            if (res4 == n4) {
                                posiCer = posiCer+1;
                            }else if (res4 == n2 || res4 == n1 || res4 == n3 || res4 == n5) {
                                posiErr = posiErr+1;
                            }

                            if (res5 == n5) {
                                posiCer = posiCer+1;
                            }else if (res5 == n2 || res5 == n1 || res5 == n3 || res5 == n4) {
                                posiErr = posiErr+1;
                            }

                            //Pega o verificador e mostra o resultado na tela
                            if (posiCer == 5) {
                                cout<<"Você acertou parabéns\n\n";
                                system("pause");
                                break;
                            }

                            if (posiCer != 5 || posiCer != 0) {
                                cout<<"Você acertou tantos "<< posiErr << " números em posições erradas.\n";
                                cout<<"Você acertou tantos "<< posiCer << " números em posições corretas.\n";
                                cout<<"Você tem mais "<< 11-tent << " tentativas.\n\n";
                            }

                            if (posiErr == 0 && posiCer == 0) {
                                cout<<"Você não acertou nada";
                            }

                            tent++;
                            if (tent == 13) {
                                cout<<"Você perdeu acabou suas tentativas\n";
                                system("pause");
                            }
                        }
                        tent = 0;
                        posiCer = 0;
                        break;
                }
                break;
            case 2:
                cout<<"Dificuldade\n\n";
                cout<<"Selecione sua dificuldade\n";
                cout<<"Fácil: 1\n";
                cout<<"Médio: 2\n";
                cout<<"Dificil: 3\n";
                cin>>dificuldade;
                system("cls");
                break;
            case 3:
                cout<<"Sobre\n";
                cout<<"Criadores:\n";
                cout<<"Daniel Machado Nascimento '-'\n";
                cout<<"Luiz Antonio Haenisch :P\n";
                cout<<"Vitória Araújo Silveira :V\n";
                cout<<"Professor: Alex Luciano Roesler Rese XD\n";
                cout<<"Feito em Outubro de 2023\n";
                system("pause");
                system("cls");
                break;
            case 4:
                cout<<"Regras\n";
                cout<<"Você apenas pode escolher de 1 a 6\n";
                cout<<"Dependendo da dificuldade aumenta as tentativas e os números que você deve advinhar\n";
                cout<<"Os números não se repetem.\n";
                cout<<"Fácil: 3 números e apenas 8 tentativas.\n";
                cout<<"Médio: 4 números e apenas 10 tentativas.\n";
                cout<<"Difícil: 5 números e apenas 12 tentativas.\n";
                system("pause");
                system("cls");
                break;
            case 5:
                cout<<"Obrigado por jogar";
                break;
            default:
                cout<<"Este número não é permitido digite: 1, 2, 3 ou 4\n";
        }
    } while (menu != 5);
    return 0;
}
