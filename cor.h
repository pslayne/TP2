#include <iostream>
#ifndef COR_H
#define COR_H 
using namespace std;

//enumera��o para criar as constantes das cores
enum cores { vermelho, azul, branco, verde, amarelo };

//fun��o para ler as cores
istream& operator>>(istream& is, cores& c);

#endif