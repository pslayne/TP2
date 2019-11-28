#include <iostream>
#ifndef COR_H
#define COR_H 
using namespace std;

//enumeração para criar as constantes das cores
enum cores { vermelho, azul, branco, verde, amarelo };

//função para ler as cores
istream& operator>>(istream& is, cores& c);

#endif