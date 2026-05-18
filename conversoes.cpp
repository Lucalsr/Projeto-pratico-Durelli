#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string divisoessucessivas(float decimal, int basefinal);
double binariopdecimalposicional(string binario);
int main()
{
    int basefinal;
    float numero;
    cin >> numero >> basefinal;
    cout << divisoessucessivas(numero, basefinal);
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

double binariopdecimalposicional(string binario)
{
    int i = 0;
    float total = 0;
    int tamanho = binario.length();
    string decimal = "";
    while(i < tamanho)
    {
        int caracter = (int)(binario[tamanho - (i + 1)]) - '0';
        caracter = pow(2, i) * caracter;
        total += caracter;
        i++;
    }
    return total;

}
