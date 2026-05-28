#include "conversoes.h" 
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string divisoessucessivas(double decimal, int basefinal)  //decimal para outras bases
{
    long long parteinteira = (long)decimal;
    double partefracionada = 0;              //separa parte inteira da fracionada
    partefracionada = decimal - parteinteira;
    string numero = "";
    string str_fracionada = "";
    int precisao_decimal = 16; //define limite de caracteres fracionarios
    int casas = 0;
    
    if(partefracionada > 0)
    {
        while(partefracionada > 1e-9 && casas < precisao_decimal) //converte parte fracionada em caracter da base escolhida
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
        
        // indica quando houver truncamento
        if(partefracionada > 1e-9)
        {
            cout << "\n[Aviso - Requisito F6] Houve truncamento! A parte fracionaria excedeu o limite de " << precisao_decimal << " casas.\n";
        }
    }
    
    if (parteinteira == 0)
    {
        numero = "0";
    }
    while(parteinteira > 0)
    {
        long long resto = 0;
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
        double caracter = (int)(parteinteira[tamanhointeiro - (i + 1)]) - '0';     //transforma parte inteira em base 10
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

string agrupamentobits(string binario, int base_destino) // converte binario para octal ou hexadecimal agrupando bits
{
    int tamanho_grupo;
    // tamanho do grupo (3 bits para octal e 4 bits para hexa)
    if (base_destino == 8) {
        tamanho_grupo = 3;
    } else if (base_destino == 16) {
        tamanho_grupo = 4;
    } else {
        return ""; 
    }

    size_t ponto = binario.find_first_of(".,");
    string parteinteira = "";
    string partefracionada = "";

    // separa o numero binario em parte inteira e fracionada
    if(ponto != std::string::npos)
    {
        parteinteira = binario.substr(0, ponto);
        partefracionada = binario.substr(ponto + 1);
    }
    else
    {
        parteinteira = binario;
    }

    // adiciona zero na esquerda ate q seja multiplo do tamanho do gp
    while (parteinteira.length() % tamanho_grupo != 0) {
        parteinteira = "0" + parteinteira;
    }

    // adiciona zeros na direita da parte fracionada até q seja múltiplo do tamanho do gp
    if (partefracionada.length() > 0) {
        while (partefracionada.length() % tamanho_grupo != 0) {
            partefracionada = partefracionada + "0";
        }
    }

    string resultado_inteiro = "";
    
    // percorre a parte inteira calculando o valor daquele bloco
    for (size_t i = 0; i < parteinteira.length(); i += tamanho_grupo) {
        string grupo = parteinteira.substr(i, tamanho_grupo);
        int valor = 0;
        for (int j = 0; j < tamanho_grupo; j++) {
            valor += (grupo[j] - '0') * pow(2, tamanho_grupo - 1 - j);
        }
        
        if (valor > 9) {
            resultado_inteiro += (char)(valor + 55); // Letras A-F para hexadecimal
        } else {
            resultado_inteiro += (char)(valor + '0'); // Números de 0-9
        }
    }

    if (resultado_inteiro == "") resultado_inteiro = "0";

    // a mesma coisa de agrupar em blocos mas pra parte fracionada(se ela existir)
    if (partefracionada.length() > 0) {
        string resultado_fracionado = "";
        for (size_t i = 0; i < partefracionada.length(); i += tamanho_grupo) {
            string grupo = partefracionada.substr(i, tamanho_grupo);
            int valor = 0;
            for (int j = 0; j < tamanho_grupo; j++) {
                valor += (grupo[j] - '0') * pow(2, tamanho_grupo - 1 - j);
            }
            if (valor > 9) {
                resultado_fracionado += (char)(valor + 55);
            } else {
                resultado_fracionado += (char)(valor + '0');
            }
        }
        return resultado_inteiro + "." + resultado_fracionado;
    }

    return resultado_inteiro;
}

string desagrupamentobits(string numero, int baseinicial)
{
    int tamanho_grupo;
    if (baseinicial == 8) {
        tamanho_grupo = 3;
    } else if (baseinicial == 16) {
        tamanho_grupo = 4;
    } else {
        return ""; 
    }

    string binario = "";

    // Percorre a string original caractere por caractere
    for (size_t i = 0; i < numero.length(); i++) 
    {
        char c = numero[i];
        if (c == '.' || c == ',')
        {
            binario += c;
        }
        else
        {
            int valor = 0;
            if (c >= '0' && c <= '9') 
            {
                valor = c - '0';
            } 
            else if (c >= 'A' && c <= 'F') 
            {
                valor = c - 55; 
            }

            string grupo_binario = "";
            for (int j = 0; j < tamanho_grupo; j++) 
            {
                char bit = (char)((valor % 2) + '0'); 
                grupo_binario = bit + grupo_binario; 
                valor = valor / 2;
            }
            binario += grupo_binario;
        }
    }
    return binario;
}

