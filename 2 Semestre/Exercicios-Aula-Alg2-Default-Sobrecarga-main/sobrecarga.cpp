#include <iostream>
#include <locale.h>

using namespace std;

double formulaGeo(double valor1){
    double area;

    area = valor1 * valor1;
    return (area);
}

double formulaGeo (double valor1, double valor2) {
    double area;

    area = valor1 * valor2;
    return (area);
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    double valor1, valor2, valor3;

    cout<<"Qual forma géometrica você quer? (Quadrado 1 valor, Circulo 2 valores, Triangulo 3)"<<endl;
    cin>>valor1;
    cin>>valor2;
    cin>>valor3;

    cout<<"A aréa do quadrado é:" <<formulaGeo(valor1)<<endl;
    cout<<"A aréa do retângulo é:" <<formulaGeo(valor1,valor2)<<endl;

    

    return 0;
}
