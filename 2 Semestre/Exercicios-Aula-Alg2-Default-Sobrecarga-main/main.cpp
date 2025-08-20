#include <iostream>
#include <locale.h>

using namespace std;

double calcularPrecoBebida (string tipoBebida = "cafe", bool comLeiteExtra = false, bool semAcucar = false, string tamanho = "medio") {
    double preco = 0;
    if (tipoBebida == "cafe") {
        preco += 2.50;
    } else if (tipoBebida == "cha") {
        preco += 2.00;
    }

    if (comLeiteExtra == false) {
        preco = preco;
    } else {
        preco += 0.50;
    }

    if (semAcucar == false) {
        preco -= 0.25;
    } else {
        preco = preco;
    }

    if (tamanho == "pequeno") {
        preco = preco;
    } else if (tamanho == "medio") {
        preco += 0.75;
    } else {
        preco += 1.50;
    }

    return (preco);
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    string tipoBebida;
    bool comLeiteExtra;
    bool semAcucar;
    string tamanho;

    cout<<"Boa tarde, bem vindo a cafeteria renatão café, você deseja café ou chá?"<<endl;
    cin>>tipoBebida;
    cout<<"Com leite extra?"<<endl;
    cin>>comLeiteExtra;
    cout<<"Com açúcar ou sem?"<<endl;
    cin>>semAcucar;
    cout<<"Qual tamanho senhor?"<<endl;
    cin>>tamanho;

    cout<<"O preço ficou:"<<endl<<calcularPrecoBebida(tipoBebida, comLeiteExtra, semAcucar, tamanho)<<endl;
    cout<<"Tenha um otimo dia";
}
