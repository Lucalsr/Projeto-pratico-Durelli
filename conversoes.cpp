#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string divisoessucessivas(float decimal, int basefinal);
double somatorioposicionalparadecimal(string numero, int baseinicial);
int main()
{
    int basefinal;
    string numero;
    cin >> numero >> basefinal;
    cout << somatorioposicionalparadecimal(numero, basefinal);
}
string divisoessucessivas(float decimal, int basefinal)
{
    int decimalh = (int)decimal;
    string numero = "";
    while(decimalh > 0)
    {
        int resto = 0;
        resto = decimalh % basefinal;
        decimalh /= basefinal;
        if(resto > 9)
        {
           numero = (char)(resto + 55) + numero;
            
        }
        else
        {
            numero = (char)(resto + '0') + numero;
        }
    }
    return numero;
}

double somatorioposicionalparadecimal(string numero, int baseinicial)
{
    int i = 0;
    float total = 0;
    int tamanho = numero.length();
    string decimal = "";
    while(i < tamanho)
    {
        int caracter = (int)(numero[tamanho - (i + 1)]) - '0';
        if(caracter > 10)
        {
            caracter -= 7;
        }
        caracter = pow(baseinicial, i) * caracter;
        total += caracter;
        i++;
    }
    return total;

}
