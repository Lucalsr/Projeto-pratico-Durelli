#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "parser.h"
#include "conversoes.h"

using namespace std;

void testar_parser() {
    cout << "[TESTE] Executando testes do Parser..." << endl;

    // 1 a 8: Testes de análise de bases numéricas suportadas e não suportadas
    assert(analise_bases(2) == true);
    assert(analise_bases(8) == true);
    assert(analise_bases(10) == true);
    assert(analise_bases(16) == true);
    assert(analise_bases(3) == false);  // Base 3 não suportada
    assert(analise_bases(20) == false); // Base 20 não suportada
    assert(analise_bases(0) == false);  // Base 0 não existe
    assert(analise_bases(-2) == false); // Base negativa

    // 9 a 17: Testes de integridade de valores inteiros nas respectivas bases
    assert(analise_valor_recebido("101011", 2) == true);
    assert(analise_valor_recebido("1012", 2) == false);  // '2' inválido em binário
    assert(analise_valor_recebido("7065", 8) == true);
    assert(analise_valor_recebido("89", 8) == false);    // '8' e '9' inválidos em octal
    assert(analise_valor_recebido("12390", 10) == true);
    assert(analise_valor_recebido("12A", 10) == false);  // Letras inválidas em decimal
    assert(analise_valor_recebido("1A9F", 16) == true);
    assert(analise_valor_recebido("1G9", 16) == false);  // 'G' inválido em hexadecimal
    assert(analise_valor_recebido("1a9f", 16) == false); // O código atual não suporta minúsculas

    // 18 a 23: Testes de ponto flutuante e separadores (vírgula/ponto)
    assert(analise_valor_recebido("10.11", 2) == true);
    assert(analise_valor_recebido("10,1", 2) == true);
    assert(analise_valor_recebido("7.5", 8) == true);
    assert(analise_valor_recebido("99.9", 10) == true);
    assert(analise_valor_recebido("F.A", 16) == true);
    assert(analise_valor_recebido("F,A", 16) == true);

    cout << "  -> 23 testes do Parser passaram com sucesso!\n";
}

void testar_conversoes() {
    cout << "[TESTE] Executando testes de Conversoes..." << endl;

    // 24 a 30: Teste somatorioposicional (Qualquer base -> Decimal)
    assert(somatorioposicional("0", 2) == 0.0);
    assert(somatorioposicional("1010", 2) == 10.0);
    assert(somatorioposicional("10.1", 2) == 2.5);
    assert(somatorioposicional("12", 8) == 10.0);
    assert(somatorioposicional("77", 8) == 63.0);
    assert(somatorioposicional("A", 16) == 10.0);
    assert(somatorioposicional("FF", 16) == 255.0);

    // 31 a 37: Teste divisoessucessivas (Decimal -> Qualquer base)
    assert(divisoessucessivas(0, 2) == "0");
    assert(divisoessucessivas(10, 2) == "1010");
    assert(divisoessucessivas(2.5, 2) == "10.1"); // Trata fracionário
    assert(divisoessucessivas(10, 8) == "12");
    assert(divisoessucessivas(63, 8) == "77");
    assert(divisoessucessivas(255, 16) == "FF");
    assert(divisoessucessivas(10.5, 16) == "A.8"); // Trata fracionário

    // 38 a 43: Teste agrupamentobits (Binário -> Octal/Hexa)
    assert(agrupamentobits("0", 16) == "0"); 
    assert(agrupamentobits("1010", 16) == "A");
    assert(agrupamentobits("11111111", 16) == "FF");
    assert(agrupamentobits("10.1", 16) == "2.8"); // Agrupa após o ponto
    assert(agrupamentobits("1010", 8) == "12");
    assert(agrupamentobits("111", 8) == "7");

    // 44 a 47: Teste desagrupamentobits (Octal/Hexa -> Binário)
    assert(desagrupamentobits("7", 8) == "111");
    assert(desagrupamentobits("F", 16) == "1111");
    assert(desagrupamentobits("12", 8) == "001010"); // Mantém zeros à esquerda
    assert(desagrupamentobits("A.8", 16) == "1010.1000"); // Desagrupa parte fracionária

    // 48 a 52: Testes de resultadoconversoes (Fluxos completos de integração)
    // Conversões pra base 10 geram string com precisão de float, usamos stod() para ignorar zeros extras
    assert(stod(resultadoconversoes("1010", 2, 10)) == 10.0);
    assert(resultadoconversoes("1010", 2, 2) == "1010"); // Mesma base origem-destino
    assert(resultadoconversoes("FF", 16, 2) == "11111111");
    assert(resultadoconversoes("12", 8, 2) == "001010");
    assert(resultadoconversoes("A", 16, 8) == "12"); // Hexa -> Binário intermediário -> Octal

    cout << "  -> 29 testes de Conversoes passaram com sucesso!\n";
}

int main() {
    cout << "========================================" << endl;
    cout << "        INICIANDO SUITE DE TESTES       " << endl;
    cout << "========================================\n" << endl;
    
    testar_parser();
    testar_conversoes();
    
    cout << "========================================" << endl;
    cout << "        TODOS OS 52 TESTES PASSARAM!    " << endl;
    cout << "========================================" << endl;
    
    return 0;
}