#include "parser.h"
#include "conversoes.h"
#include "formatador.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
void verificarintegridade(string &numero, int &baseinicial, int &basefinal);
string resultadoconversoes(string numero, int baseinicial, int basefinal);
void modo_batch();
void calculadora_maximos(int bits);

int main()
{
    string numero = " ";
    int baseinicial, basefinal;
    int controladorloop = 0;
    while(controladorloop == 0)
    {
        int escolha;
        imprimir_cabecalho();
        imprimir_menu_modos();
        cin >> escolha;
        if(escolha >= 1 || escolha <= 5)
        {
            controladorloop = 1;
            cout << system("cls");
        }
        else
        {
            cout << "Nao ha essa opcao!";
        }
        if(escolha == 1)
        {
            verificarintegridade(numero, baseinicial, basefinal);
            cout << resultadoconversoes(numero, baseinicial, basefinal);
        }
        else if(escolha == 3)
        {
            modo_batch();
        }
        else if(escolha == 5)
        {
            long bits = 0;
            cout << "Quantos numeros de bits voce deseja calcular o maximo de cada base?: ";
            cin >> bits;
            calculadora_maximos(bits);
        }
        cout << "Aperte enter para fechar....";
        cin.ignore();
        cin.get();
    }
    
   
}
void verificarintegridade(string &numero, int &baseinicial, int &basefinal)
{
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

}

string resultadoconversoes(string numero, int baseinicial, int basefinal)
{
    string numerofinal = "";
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
            numerofinal = to_string(somatorioposicional(numero, baseinicial));
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
            numerofinal = to_string(somatorioposicional(numero, baseinicial));
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
            numerofinal = to_string(somatorioposicional(numero, baseinicial));
        }
        else
        {
            numerofinal = numero;
        }
    }
    return numerofinal;
}

void modo_batch()
{
    ifstream arqdados("entrada.csv");
    string valor, base_int, valorsaida = " ";
    int baseinicial, basefinal;
    ofstream dadossaida("saida.csv");
    while(getline(arqdados, valor, ';'))    
    {
        getline(arqdados, base_int, ';');
        baseinicial = stoi(base_int);
        getline(arqdados, base_int, '\n');
        basefinal = stoi(base_int);
        valorsaida = resultadoconversoes(valor, baseinicial, basefinal);
        dadossaida << valor << ";" << baseinicial << ";" << valorsaida << ";" << basefinal << endl;
    }
    cout << "Arquivo 'saida.csv' gerado." << endl;
    arqdados.close();
    dadossaida.close();
}

void calculadora_maximos(int bits)
{
    string maximo_binario, maximo_octal, maximo_decimal, maximo_hexa;
    int reserva;
    reserva = pow(2, bits) - 1;
    maximo_decimal = to_string(reserva);
    maximo_binario = divisoessucessivas(reserva, 2);
    maximo_octal = divisoessucessivas(reserva, 8);
    maximo_hexa = divisoessucessivas(reserva, 16);
    cout << "Binario: " << maximo_binario << endl;
    cout << "Octal: " << maximo_octal << endl;
    cout << "Decimal: " << maximo_decimal << endl;
    cout << "Hexadecimal: " << maximo_hexa << endl;
}
