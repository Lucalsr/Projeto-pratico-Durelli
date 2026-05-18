#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string divisoessucessivas(float decimal, int basefinal);
double somatorioposicional(string numero, int baseinicial);
int main()
{
    int basefinal;
    string numero;
    cin >> numero >> basefinal;
    cout << somatorioposicional(numero, basefinal);
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

double somatorioposicional(string numero, int baseinicial)
{
    size_t ponto = numero.find_first_of(".,");
    string parteinteira = "";
    string partefracionada = "";
    if(ponto != std::string::npos)
    {
        parteinteira = numero.substr(0, ponto);
        partefracionada = numero.substr(ponto + 1);
    }
    else
    {
        parteinteira = numero;
    }
    int i = 0;
    double total = 0;
    int tamanhointeiro = parteinteira.length();
    while(i < tamanhointeiro)
    {
        int caracter = (int)(parteinteira[tamanhointeiro - (i + 1)]) - '0';
        if(caracter > 9)
        {
            caracter -= 7;
        }
        caracter = pow(baseinicial, i) * caracter;
        total += caracter;
        i++;
    }
    int tamanhofracionada = partefracionada.length();
    int j = 0;
    while(j < tamanhofracionada)
    {
        double caracter = (int)(partefracionada[j] - '0');
        if(caracter > 9)
        {
            caracter -= 7;
        }
        caracter = pow(baseinicial, -(j + 1)) * caracter;
        total += caracter;
        j++;
    }
    return total;

}
