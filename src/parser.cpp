#include "parser.h"

bool analise_bases(int base)
{
    if(base == 2 || base == 8 || base == 16 || base == 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool analise_valor_recebido(string numero, int base)
{
    if(base == 2)
    {
        for(size_t i = 0; i < numero.length(); i++)
        {
            char c = numero[i];
            if (c == '.' || c == ','){
                    continue;
                }
            if(c != '0' && c != '1')
            {
                 return false;
            }
            }
        }
    else if(base == 8)
    {
        for(size_t i = 0; i < numero.length(); i++)
        {
            char c = numero[i];
            if (c == '.' || c == ','){
                continue;
            }
            if(c < '0' || c > '7')
            {
                return false;
            }
        }
    }
    else if(base == 10)
    {
        for(size_t i = 0; i < numero.length(); i++)
        {
            char c = numero[i];
            if (c == '.' || c == ','){
                continue;
            }
            if(c < '0' || c > '9')
            {
                return false;
            }
        }
    }
    else if(base == 16)
    {
        for(size_t i = 0; i < numero.length(); i++)
        {
            char c = numero[i];
            if (c == '.' || c == ','){
                continue;
            }
            if(!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
            {
                return false;
            }
        }
    }
    return true;
}