#include <iostream>
using namespace std;
string decimalparabinario(float decimal);
string decimalparaoctal(float decimal);
string decimalparahexa(float decimal);
int main()
{
    float decimal;
    cin >> decimal;
    cout << decimalparabinario(decimal) << endl << decimalparaoctal(decimal) << endl << decimalparahexa(decimal);
}
string decimalparabinario(float decimal)
{
    int decimalt = (int)decimal;
    string binario = "";
    while(decimalt > 0)
    {
        binario = char((decimalt % 2) + '0') + binario;
        decimalt /= 2; 
    }
    return binario;
}

string decimalparaoctal(float decimal)
{
    int decimalo = (int)decimal;
    string octal = "";
    while(decimalo > 0)
    {
        octal = char((decimalo % 8) + '0') + octal;
        decimalo /= 8;
    }
    return octal;
}

string decimalparahexa(float decimal)
{
    int decimalh = (int)decimal;
    string hexadecimal = "";
    while(decimalh > 0)
    {
        int resto = 0;
        resto = decimalh % 16;
        decimalh /= 16;
        if(resto > 9)
        {
           hexadecimal = (char)(resto + 55) + hexadecimal;
            
        }
        else
        {
            hexadecimal = (char)(resto + '0') + hexadecimal;
        }

    }
    return hexadecimal;


}
