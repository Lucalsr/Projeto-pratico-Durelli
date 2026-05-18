#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string divisoessucessivas(double decimal, int basefinal);
double somatorioposicional(string numero, int baseinicial);
int main()
{
    int basefinal;
    double numero;
    cin >> numero >> basefinal;
    cout << divisoessucessivas(numero, basefinal);
}
string divisoessucessivas(double decimal, int basefinal)  //decimal para outras bases
{
    long parteinteira = (long)decimal;
    double partefracionada = 0;              //separa parte inteira da fracionada
    partefracionada = decimal - parteinteira;
    string numero = "";
    string str_fracionada = "";
    int precisao_decimal = 16; //define limite de caracteres fracionarios
    int casas = 0;
    if(partefracionada > 0)
    {
        while(partefracionada > 0 && casas < precisao_decimal) //converte parte fracionada em caracter da base escolhida
        {
            partefracionada *= basefinal;
            int fracaoquevai = (int)partefracionada;
            if(fracaoquevai > 9)                             
            {
                str_fracionada = str_fracionada + (char)(fracaoquevai + 55);         
                                                                                    
            }                                                                            
            else
            {
                str_fracionada = str_fracionada + (char)(fracaoquevai + '0');
            }
            partefracionada -= fracaoquevai;
            casas++;
        }
    }
    if (parteinteira == 0)
    {
        numero = "0";
    }
    while(parteinteira > 0)
    {
        int resto = 0;
        resto = parteinteira % basefinal;
        parteinteira /= basefinal;
        if(resto > 9)
        {
           numero = (char)(resto + 55) + numero; //converte parte inteira para o caracter da base escolhida
        }
        else
        {
            numero = (char)(resto + '0') + numero;
        }
    }
    if(str_fracionada != "")
    {
        return numero + "." + str_fracionada;
    }
    else
    {
        return numero;
    }
}

double somatorioposicional(string numero, int baseinicial) //outras bases para decimal
{
    size_t ponto = numero.find_first_of(".,");
    string parteinteira = "";
    string partefracionada = "";
    if(ponto != std::string::npos)
    {
        parteinteira = numero.substr(0, ponto);        //separa parte fracionada e inteira de qualquer base
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
        int caracter = (int)(parteinteira[tamanhointeiro - (i + 1)]) - '0';     //transforma parte inteira em base 10
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
        double caracter = (int)(partefracionada[j] - '0');      //transforma parte fracionaria em base 10
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
