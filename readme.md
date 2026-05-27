# Alunos participando:
1. Lucas de Sousa Rodrigues
2. Guilherme Oliveira Brito
# Conversor de Bases Numéricas

Este é um projeto em C++ desenvolvido para conversão de números entre diferentes bases numéricas (Binário, Octal, Decimal e Hexadecimal), com suporte completo a números inteiros e fracionários (ponto flutuante).

## Como Funciona

O programa oferece 5 modos principais de operação através de um menu interativo:
1. **Conversão Direta:** Converte um número de uma base para outra de forma direta.
2. **Modo Passo-a-Passo (Trace):** Exibe detalhadamente o algoritmo utilizado na conversão (ex: divisões sucessivas, somatório posicional ou agrupamento de bits).
3. **Modo Batch:** Processa em lote um arquivo de entrada (`entrada.csv`) e gera um arquivo de resultados (`saida.csv`).
4. **Modo Quiz:** Um jogo de perguntas e respostas com 5 níveis de dificuldade para testar conhecimentos em conversão de bases.
5. **Calculadora de Máximos:** Calcula o maior valor que pode ser representado em cada base dado um número limite de bits.

---

## Organização do Projeto

A estrutura de arquivos do projeto está organizada da seguinte forma:

```text
PROJETO-PRATICO-DURELLI/
├── output/                  # Executáveis gerados após a compilação
│   ├── main.exe             # Programa principal
│   └── conversoes.exe       # Suíte de testes automatizados
├── src/                     # Código-fonte principal do sistema
│   ├── conversoes.cpp / .h  # Algoritmos de conversão
│   ├── formatador.cpp / .h  # Funções de interface e menus
│   ├── main.cpp             # Ponto de entrada do programa principal
│   └── parser.cpp / .h      # Validação de bases e entradas
├── testes/                  # Testes do sistema
│   └── suitedetestes.cpp    # Suíte de testes automatizados (+30 casos)
└── readme.md                # Documentação do projeto

```
## Código para compilar:
Compilar o código main: \
g++ src/main.cpp src/conversoes.cpp src/formatador.cpp src/parser.cpp -I src -o output/main.exe \
Compilar o a suíte de testes: \
g++ testes/suitedetestes.cpp src/conversoes.cpp src/formatador.cpp src/parser.cpp -I src -o output/conversoes.exe 
