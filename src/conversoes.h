#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>
using namespace std;

string divisoessucessivas(double decimal, int basefinal);

double somatorioposicional(string numero, int baseinicial);

string agrupamentobits(string binario, int base_destino);

string desagrupamentobits(string numero, int baseinicial);

#endif