#include <iostream>
using namespace std;

template <typename T>
struct No{
    T info;
    No <T> *esq=NULL, *dir=NULL;
};

template <typename T>
void prefixado(No <T> *raiz){
    if( raiz == NULL ) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

template <typename T>
void infixado(No <T> *raiz){
    if( raiz == NULL ) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}

template <typename T>
void posfixado(No <T> *raiz){
    if( raiz == NULL ) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}

template <typename T>
int contar(No <T> *raiz){
    if( raiz == NULL ) return 0;
    return 1 + contar(raiz->esq) + contar(raiz->dir);
}

template <typename T>
bool inserirABB( No <T> *&raiz, T info ){
    if( raiz == NULL ){
        raiz = new No<T>;
        if( raiz == NULL ) return false;  // Memoria cheia
        raiz->info = info;
        return true;
    }
    if( info == raiz->info ) return false; // Chave duplicada
    if( info < raiz->info )
        return inserirABB(raiz->esq, info);
    else
        return inserirABB(raiz->dir, info);
}

template <typename T>
T buscar_maior_valor(No <T> *raiz){
    if( raiz->dir == NULL )
        return raiz->info;
    else
        return buscar_maior_valor(raiz->dir);
}

template <typename T>
bool retirarABB( No <T> *&raiz, T info ){
    if( raiz == NULL ) return false;
    if( info == raiz->info ){
        No <T> *aux = raiz;
        if( raiz->esq == NULL && raiz->dir == NULL ){ // É folha
            raiz = NULL;
        }
        else if( raiz->esq != NULL && raiz->dir == NULL ){ // So tem filho a esquerda
            raiz = raiz->esq;
        }
        else if( raiz->esq == NULL && raiz->dir != NULL ){ // So tem filho a direira
            raiz = raiz->dir;
        }
        else{ // Tem dois filhos
            T aux2 = buscar_maior_valor(raiz->esq);
            raiz->info = aux2;
            return retirarABB(raiz->esq, aux2);
        }
        delete aux;
        return true;
    }
    if( info < raiz->info )
        return retirarABB(raiz->esq, info);
    else
        return retirarABB(raiz->dir, info);
}

template <typename T>
bool pesquisarABB(No <T> *raiz, T info){
    if( raiz == NULL ) return false;
    if( info == raiz->info ) return true;
    if( info < raiz->info )
        return pesquisarABB(raiz->esq, info);
    else
        return pesquisarABB(raiz->dir, info);
}

template <typename T>
void liberarABB(No <T> *&raiz){
    if( raiz == NULL ) return;
    liberarABB(raiz->esq);
    liberarABB(raiz->dir);
    delete raiz;
}

template <typename T>
int contarFolhas(No <T> *raiz) {
    if( raiz == NULL ) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) {
        return 1;
    }
    else{
        return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
    }
}

template <typename T>
int contarApenas1(No <T> *raiz) {
    if( raiz == NULL ) return 0;
    if (raiz->esq != NULL && raiz->dir == NULL) {
        return 1;
    } else if (raiz->esq == NULL && raiz->dir != NULL) {
        return 1;
    } else {
        return contarApenas1(raiz->esq) + contarApenas1(raiz->dir);
    }
}
