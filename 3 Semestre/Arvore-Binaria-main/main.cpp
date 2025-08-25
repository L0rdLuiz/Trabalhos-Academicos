#include <iostream>
#include "abb.hpp"
using namespace std;

int main(){
    No <int> *raiz=NULL;
    int opcao, valor;

    do{
        cout << endl << endl << "Arvore binaria de busca:";
        cout << endl << "\t1 - Inserir";
        cout << endl << "\t2 - Retirar";
        cout << endl << "\t3 - Pesquisar";
        cout << endl << "\t4 - Caminhamento Pre-fixado";
        cout << endl << "\t5 - Caminhamento Infixado";
        cout << endl << "\t6 - Caminhamento Pos-fixado";
        cout << endl << "\t7 - Contar nos";
        cout << endl << "\t8 - Contar folhas";
        cout << endl << "\t9 - Contar Apenas um Filho";
        cout << endl << "\t0 - Fim";
        cout << endl << "Opcao: ";
        cin >> opcao;

        switch(opcao){
            case 0: // Sair
                break;
            case 1: // Inserir
                cout << endl << "Valor a inserir: ";
                cin >> valor;
                if( inserirABB(raiz, valor) )
                    cout << "Valor inserido com sucesso!";
                else
                    cout << "Erro na insercao";
                break;
            case 2: // Retirar
                cout << endl << "Valor a retirar: ";
                cin >> valor;
                if( retirarABB(raiz, valor) )
                    cout << "Valor retirado da arvore!";
                else
                    cout << "Valor nao presente na arvore";
                break;
            case 3: // Pesquisar
                cout << endl << "Valor a pesquisar: ";
                cin >> valor;
                if( pesquisarABB(raiz, valor) )
                    cout << "Valor localizado na arvore!";
                else
                    cout << "Valor nao presente na arvore";
                break;
            case 4: // Pre-fixado
                cout << endl << "Pre-fixado: ";
                prefixado(raiz);
                break;
            case 5: // Infixado+
                cout << endl << "Infixado: ";
                infixado(raiz);
                break;
            case 6: // Pos-fixadp
                cout << endl << "Pos-fixado: ";
                posfixado(raiz);
                break;
            case 7: // Contar nos
                cout << endl << "Numero de nos na arvore: " << contar(raiz);
                break;
            case 8: // Contar folhas
                cout<< endl << "Numero de folhas na arvore: " << contarFolhas(raiz);
                break;
            case 9: //Contar quando tem apenas um filho
                cout << endl << "Numero de raizes com apenas um filho: " << contarApenas1(raiz);
                break;
            default:
                cout << endl << "Erro, opcao invalida!";
        }
    }while( opcao != 0 );

    liberarABB(raiz);
    cout << endl;
}
