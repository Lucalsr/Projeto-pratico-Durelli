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
    int baseinicial, basefinal;
    bool verificadorbaseinicial = false;
    cout << "Qual a base numerica inicial do numero?" << endl << "Escreva de forma numerica: ";
    while(!verificadorbaseinicial)
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
    while(!verificadornumero)
    {
        cin >> numero;
        if(analise_valor_recebido(numero, baseinicial))
        {
            verificadornumero = true;
        }
        else if(!verificadornumero)
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
    while(!verificadorbasefinal)
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

}