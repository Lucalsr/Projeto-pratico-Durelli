#include "parser.h"
#include "conversoes.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string numero = "";
    string numerofinal = "";
    int baseinicial, basefinal;
    bool verificadorbaseinicial = false;
    cout << "Qual a base numerica inicial do numero?" << endl << "Escreva de forma numerica: ";
    while(!verificadorbaseinicial)    //verificar se a base inicial inserida e suportado
    {
        cin >> baseinicial;
        if(analise_bases(baseinicial))
        {
            verificadorbaseinicial = true;
        }
        else
        {
            cout << "Base nao suportada." << endl << "Escolha entre 2,8,10 e 16: ";
        }
    }
    bool verificadornumero = false;
    cout << "Escreva o valor a ser transformado: ";
    while(!verificadornumero)                     //verificar se o numero inserido condiz com a base fornecida
    {
        cin >> numero;
        if(analise_valor_recebido(numero, baseinicial))
        {
            verificadornumero = true;
        }
        else
        {
            if(baseinicial == 16)
            {
                cout << "Caso tenha, o codigo nao suporta letras minusculas" << endl;
            }
            cout << "Valor com algarismos que nao condizem com a base escolhida." << endl << "Informe o numero novamente: "; 
        }
    }
    bool verificadorbasefinal = false;
    cout << "Qual a base numerica para a qual o valor sera transformado?" << endl << "Escreva de forma numerica: ";
    while(!verificadorbasefinal)            //verificar se a base final inserida e suportada
    {
        cin >> basefinal;
        if(analise_bases(basefinal))
        {
            verificadorbasefinal = true;
        }
        else
        {
            cout << "Base nao suportada." << endl << "Escolha entre 2,8,10 e 16: ";
        }
    }
    //fazer as conversões 
    if(baseinicial == 10)
    {
        if(basefinal == 10)
        {
            numerofinal = numero;
        }
        else
        {
            int numeroemint = stoi(numero);
            numerofinal = divisoessucessivas(numeroemint, basefinal);
        }
    }
    else if(baseinicial == 2)
    {
        if(basefinal == 8 || basefinal == 16)
        {
            numerofinal = agrupamentobits(numero, basefinal);
        }
        else if(basefinal == 10)
        {
            numerofinal = somatorioposicional(numero, baseinicial);
        }
        else
        {
            numerofinal = numero;
        }
    }
    else if(baseinicial == 8)
    {
        if(basefinal == 2)
        {
            numerofinal = desagrupamentobits(numero, baseinicial);
        }
        else if(basefinal == 10)
        {
            numerofinal = somatorioposicional(numero, baseinicial);
        }
        else if(basefinal == 16)
        {
            string octembits = "";
            octembits = desagrupamentobits(numero, baseinicial);
            numerofinal = agrupamentobits(octembits, basefinal);
        }
        else
        {
            numerofinal = numero;
        }
    }
    else if(baseinicial == 16)
    {
        if(basefinal == 2)
        {
            numerofinal = desagrupamentobits(numero, baseinicial);
        }
        else if(basefinal == 8)
        {
            string hexaembits = "";
            hexaembits = desagrupamentobits(numero, baseinicial);
            numerofinal = agrupamentobits(hexaembits, basefinal); 
        }
        else if(basefinal == 10)
        {
            numerofinal = somatorioposicional(numero, baseinicial);
        }
        else
        {
            numerofinal = numero;
        }
    }
    cout << numerofinal << endl;
}