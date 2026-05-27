#include "conversoes.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Variaveis globais para controle dos testes
int testes_passados = 0;
int testes_falhados = 0;

// Macro para facilitar a escrita e validacao dos testes
#define TEST_ASSERT(condicao, nome_teste) \
    if (condicao) { \
        cout << "[PASS] " << nome_teste << "\n"; \
        testes_passados++; \
    } else { \
        cout << "[FAIL] " << nome_teste << " (Falhou na linha " << __LINE__ << ")\n"; \
        testes_falhados++; \
    }

// Funcao auxiliar para comparar doubles com precisao
bool double_equals(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

void executar_testes_parser() {
    cout << "\n--- TESTES: PARSER (Validacao de Bases e Valores) ---\n";
    
    // 1-4: analise_bases
    TEST_ASSERT(analise_bases(2) == true, "Base 2 e suportada");
    TEST_ASSERT(analise_bases(10) == true, "Base 10 e suportada");
    TEST_ASSERT(analise_bases(16) == true, "Base 16 e suportada");
    TEST_ASSERT(analise_bases(3) == false, "Base 3 NAO e suportada");

    // 5-14: analise_valor_recebido
    TEST_ASSERT(analise_valor_recebido("1010", 2) == true, "Valor binario valido");
    TEST_ASSERT(analise_valor_recebido("1012", 2) == false, "Valor binario invalido (contem 2)");
    TEST_ASSERT(analise_valor_recebido("70", 8) == true, "Valor octal valido");
    TEST_ASSERT(analise_valor_recebido("80", 8) == false, "Valor octal invalido (contem 8)");
    TEST_ASSERT(analise_valor_recebido("999", 10) == true, "Valor decimal valido");
    TEST_ASSERT(analise_valor_recebido("99A", 10) == false, "Valor decimal invalido (contem letra)");
    TEST_ASSERT(analise_valor_recebido("1A3F", 16) == true, "Valor hexadecimal valido (Maiusculo)");
    TEST_ASSERT(analise_valor_recebido("1G3F", 16) == false, "Valor hexadecimal invalido (contem G)");
    TEST_ASSERT(analise_valor_recebido("10.11", 2) == true, "Valor binario fracionario valido (Ponto)");
    TEST_ASSERT(analise_valor_recebido("10,11", 2) == true, "Valor binario fracionario valido (Virgula)");
}

void executar_testes_somatorio_posicional() {
    cout << "\n--- TESTES: SOMATORIO POSICIONAL (Qualquer Base -> Decimal) ---\n";
    
    // 15-20: somatorioposicional
    TEST_ASSERT(double_equals(somatorioposicional("1010", 2), 10.0), "Binario '1010' para Decimal 10");
    TEST_ASSERT(double_equals(somatorioposicional("11.1", 2), 3.5), "Binario '11.1' para Decimal 3.5");
    TEST_ASSERT(double_equals(somatorioposicional("17", 8), 15.0), "Octal '17' para Decimal 15");
    TEST_ASSERT(double_equals(somatorioposicional("7.4", 8), 7.5), "Octal '7.4' para Decimal 7.5");
    TEST_ASSERT(double_equals(somatorioposicional("FF", 16), 255.0), "Hexa 'FF' para Decimal 255");
    TEST_ASSERT(double_equals(somatorioposicional("A.8", 16), 10.5), "Hexa 'A.8' para Decimal 10.5");
}

void executar_testes_divisoes_sucessivas() {
    cout << "\n--- TESTES: DIVISOES SUCESSIVAS (Decimal -> Qualquer Base) ---\n";
    
    // 21-26: divisoessucessivas
    TEST_ASSERT(divisoessucessivas(10.0, 2) == "1010", "Decimal 10 para Binario '1010'");
    TEST_ASSERT(divisoessucessivas(3.5, 2) == "11.1", "Decimal 3.5 para Binario '11.1'");
    TEST_ASSERT(divisoessucessivas(15.0, 8) == "17", "Decimal 15 para Octal '17'");
    TEST_ASSERT(divisoessucessivas(7.5, 8) == "7.4", "Decimal 7.5 para Octal '7.4'");
    TEST_ASSERT(divisoessucessivas(255.0, 16) == "FF", "Decimal 255 para Hexa 'FF'");
    TEST_ASSERT(divisoessucessivas(10.5, 16) == "A.8", "Decimal 10.5 para Hexa 'A.8'");
}

void executar_testes_agrupamento_bits() {
    cout << "\n--- TESTES: AGRUPAMENTO DE BITS (Binario -> Octal/Hexa) ---\n";
    
    // 27-30: agrupamentobits
    TEST_ASSERT(agrupamentobits("1010", 16) == "A", "Agrupar '1010' (Bin) para Hexa 'A'");
    TEST_ASSERT(agrupamentobits("11111111", 16) == "FF", "Agrupar '11111111' (Bin) para Hexa 'FF'");
    TEST_ASSERT(agrupamentobits("111", 8) == "7", "Agrupar '111' (Bin) para Octal '7'");
    TEST_ASSERT(agrupamentobits("11.1", 16) == "3.8", "Agrupar '11.1' fracionario para Hexa '3.8'");
}

void executar_testes_desagrupamento_bits() {
    cout << "\n--- TESTES: DESAGRUPAMENTO DE BITS (Octal/Hexa -> Binario) ---\n";
    
    // 31-34: desagrupamentobits
    TEST_ASSERT(desagrupamentobits("A", 16) == "1010", "Desagrupar 'A' (Hexa) para Binario '1010'");
    TEST_ASSERT(desagrupamentobits("FF", 16) == "11111111", "Desagrupar 'FF' (Hexa) para Binario");
    TEST_ASSERT(desagrupamentobits("7", 8) == "111", "Desagrupar '7' (Octal) para Binario '111'");
    TEST_ASSERT(desagrupamentobits("3.8", 16) == "0011.1000", "Desagrupar '3.8' (Hexa) para Bin fracionario");
}

void executar_testes_resultado_conversoes() {
    cout << "\n--- TESTES: FLUXO COMPLETO (Resultado Conversoes) ---\n";
    
    // 35-38: resultadoconversoes (funcao principal de roteamento)
    // Nota: Como o `to_string(double)` no C++ adiciona zeros a direita (ex: 15.000000), 
    // os testes para base destino 10 verificam apenas strings para as outras bases.
    
    TEST_ASSERT(resultadoconversoes("10", 10, 10) == "10", "Base 10 -> Base 10 mantem valor");
    TEST_ASSERT(resultadoconversoes("FF", 16, 2) == "11111111", "Fluxo Completo: Hexa para Binario");
    TEST_ASSERT(resultadoconversoes("15", 10, 16) == "F", "Fluxo Completo: Decimal para Hexadecimal");
    TEST_ASSERT(resultadoconversoes("1111", 2, 8) == "17", "Fluxo Completo: Binario para Octal");
}

int main() {
    cout << "========================================\n";
    cout << "      INICIANDO SUITE DE TESTES         \n";
    cout << "========================================\n";

    executar_testes_parser();
    executar_testes_somatorio_posicional();
    executar_testes_divisoes_sucessivas();
    executar_testes_agrupamento_bits();
    executar_testes_desagrupamento_bits();
    executar_testes_resultado_conversoes();

    cout << "\n========================================\n";
    cout << "RESUMO DOS TESTES:\n";
    cout << "Passaram: " << testes_passados << "\n";
    cout << "Falharam: " << testes_falhados << "\n";
    cout << "Total:    " << (testes_passados + testes_falhados) << "\n";
    cout << "========================================\n";

    if (testes_falhados == 0) {
        cout << "\n[SUCESSO] Todos os testes passaram sem erros!\n";
        return 0;
    } else {
        cout << "\n[ATENCAO] Alguns testes falharam. Verifique os logs acima.\n";
        return 1;
    }
}