#include <iostream> 
#include "vetor.h"
#include "cor.h"
#ifndef PARTICULA_H
#define PARTICULA_H
using namespace std;

//registro para receber as part�culas
struct particula {
	char nome[20];
	position atual;
	char sistema;
	coordenada deslocamento;
	cores cor;
};

//fun��o para ler as part�culas
istream& operator>>(istream& is, particula& p);

#endif