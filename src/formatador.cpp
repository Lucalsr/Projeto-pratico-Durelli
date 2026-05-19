#include "formatador.h"
#include <iostream>
using namespace std;

void imprimir_cabecalho()
{
    cout << "========================================\n";
    cout << "           CONVERSOR DE BASES           \n";
    cout << "========================================\n\n";
}

void imprimir_menu_modos() {
    std::cout << "Escolha o modo de operacao do programa:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1 - Conversao Direta (Normal)\n";
    std::cout << "2 - Modo Passo-a-Passo (Trace de Algoritmos) [F7]\n";
    std::cout << "3 - Modo Batch (Processamento de arquivo .csv) [F8]\n";
    std::cout << "4 - Modo Quiz (Teste de Conhecimento) [F9]\n";
    std::cout << "5 - Calculadora de Maximos [F10]\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Digite o numero da opcao: ";
}