#include "parser.h"
#include "conversoes.h"
#include "formatador.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <ctime>   

using namespace std;
void verificarintegridade(string &numero, int &baseinicial, int &basefinal);
string resultadoconversoes(string numero, int baseinicial, int basefinal, bool trace = false);
void modo_batch();
void calculadora_maximos(int bits);
void modo_quiz(); 
int texto_para_inteiro(string s);

int main()
{
    srand(time(NULL)); 

    string numero = " ";
    int baseinicial, basefinal;
    int controladorloop = 0;
    while(controladorloop == 0)
    {
        int escolha;
        imprimir_cabecalho();
        imprimir_menu_modos();
        cin >> escolha;
        
        if(escolha >= 1 && escolha <= 5) 
        {
            controladorloop = 1;
            cout << system("cls");
        }
        else
        {
            cout << "Nao ha essa opcao!\n";
        }

        if(escolha == 1)
        {
            verificarintegridade(numero, baseinicial, basefinal);
            cout << "\nResultado: " << resultadoconversoes(numero, baseinicial, basefinal) << endl;
        }
        else if(escolha == 2)
        {
            cout << "\n--- MODO PASSO-A-PASSO (TRACE) ---\n";
            verificarintegridade(numero, baseinicial, basefinal);
            cout << "\nResultado Final: " << resultadoconversoes(numero, baseinicial, basefinal, true) << endl;
        }
        else if(escolha == 3)
        {
            modo_batch();
        }
        else if(escolha == 4) 
        {
            modo_quiz();
        }
        else if(escolha == 5)
        {
            long bits = 0;
            cout << "Quantos numeros de bits voce deseja calcular o maximo de cada base?: ";
            cin >> bits;
            calculadora_maximos(bits);
        }
        
        cout << "\nAperte enter para voltar ao menu....";
        cin.ignore();
        cin.get();
        controladorloop = 0; 
    }
    return 0;
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

string resultadoconversoes(string numero, int baseinicial, int basefinal, bool trace)
{
    string numerofinal = "";
    
    if(trace) {
        cout << "\n[TRACE] Iniciando conversao do valor '" << numero << "' da base " << baseinicial << " para a base " << basefinal << ".\n";
    }

    if(baseinicial == 10)
    {
        if(basefinal == 10)
        {
            numerofinal = numero;
        }
        else
        {
          
            double numerodouble = somatorioposicional(numero, baseinicial);
            
            if(trace) cout << "[TRACE] Aplicando metodo das divisoes sucessivas...\n";
            numerofinal = divisoessucessivas(numerodouble, basefinal);
        }
    }
    else if(baseinicial == 2)
    {
        if(basefinal == 8 || basefinal == 16)
        {
            if(trace) cout << "[TRACE] Aplicando agrupamento de bits...\n";
            numerofinal = agrupamentobits(numero, basefinal);
        }
        else if(basefinal == 10)
        {
            if(trace) cout << "[TRACE] Aplicando somatorio posicional...\n";
            numerofinal = divisoessucessivas(somatorioposicional(numero, baseinicial), 10);
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
            if(trace) cout << "[TRACE] Aplicando desagrupamento de bits...\n";
            numerofinal = desagrupamentobits(numero, baseinicial);
        }
        else if(basefinal == 10)
        {
            if(trace) cout << "[TRACE] Aplicando somatorio posicional...\n";
            numerofinal = divisoessucessivas(somatorioposicional(numero, baseinicial), 10);
        }
        else if(basefinal == 16)
        {
            if(trace) cout << "[TRACE] Passo 1: Desagrupando Octal para base Binaria intermediaria...\n";
            string octembits = desagrupamentobits(numero, baseinicial);
            if(trace) cout << "[TRACE] Binario intermediario gerado: " << octembits << "\n";
            if(trace) cout << "[TRACE] Passo 2: Agrupando Binario para Hexadecimal...\n";
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
            if(trace) cout << "[TRACE] Aplicando desagrupamento de bits...\n";
            numerofinal = desagrupamentobits(numero, baseinicial);
        }
        else if(basefinal == 8)
        {
            if(trace) cout << "[TRACE] Passo 1: Desagrupando Hexadecimal para base Binaria intermediaria...\n";
            string hexaembits = desagrupamentobits(numero, baseinicial);
            if(trace) cout << "[TRACE] Binario intermediario gerado: " << hexaembits << "\n";
            if(trace) cout << "[TRACE] Passo 2: Agrupando Binario para Octal...\n";
            numerofinal = agrupamentobits(hexaembits, basefinal); 
        }
        else if(basefinal == 10)
        {
            if(trace) cout << "[TRACE] Aplicando somatorio posicional...\n";
            numerofinal = divisoessucessivas(somatorioposicional(numero, baseinicial), 10);
        }
        else
        {
            numerofinal = numero;
        }
    }
    
    if(trace) cout << "[TRACE] Conversao concluida.\n";
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
        baseinicial = texto_para_inteiro   (base_int);
        getline(arqdados, base_int, '\n');
        basefinal = texto_para_inteiro(base_int);
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
    unsigned long long reserva; 
    reserva = pow(2, bits) - 1;
    maximo_decimal = divisoessucessivas(reserva, 10);
    maximo_binario = divisoessucessivas(reserva, 2);
    maximo_octal = divisoessucessivas(reserva, 8);
    maximo_hexa = divisoessucessivas(reserva, 16);
    
    cout << "Binario: " << maximo_binario << endl;
    cout << "Octal: " << maximo_octal << endl;
    cout << "Decimal: " << maximo_decimal << endl;
    cout << "Hexadecimal: " << maximo_hexa << endl;
}

void modo_quiz()
{
    int pontuacao = 0;
    int bases[] = {2, 8, 10, 16};
    
    cout << "========================================\n";
    cout << "            BEM-VINDO AO QUIZ!            \n";
    cout << "========================================\n";
    
    // niveis
    for (int nivel = 1; nivel <= 5; nivel++) {
        // sorteia 
        int id_origem = rand() % 4;
        int id_destino;
        do {
            id_destino = rand() % 4;
        } while (id_origem == id_destino);
        
        int base_origem = bases[id_origem];
        int base_destino = bases[id_destino];

        // sobe a dificuldade
        int max_val = pow(10, nivel); 
        int valor_sorteado = (rand() % max_val) + 1; 
        
        string pergunta_str = divisoessucessivas(valor_sorteado, base_origem);
        string resposta_correta = divisoessucessivas(valor_sorteado, base_destino);

        cout << "\n--- Nivel " << nivel << " ---\n";
        cout << "Converta o valor " << pergunta_str << " (Base " << base_origem << ") para a Base " << base_destino << ": ";
        
        string resposta_usuario;
        cin >> resposta_usuario;

        for (auto & c: resposta_usuario) c = toupper(c);

        if (resposta_usuario == resposta_correta) {
            cout << "Correto! Muito bem.\n";
            pontuacao += (10 * nivel);
        } else {
            cout << "Incorreto! A resposta certa era: " << resposta_correta << "\n";
        }
    }
    
    cout << "\n========================================\n";
    cout << "Fim do Quiz! Sua pontuacao final: " << pontuacao << " pontos.\n";
    cout << "========================================\n";
}

int texto_para_inteiro(string s) {
    int num = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 10 + (s[i] - '0');
        }
    }
    return num;
}
