#include <iostream> 
#include "vetor.h"
#include "cor.h"
#ifndef PARTICULA_H
#define PARTICULA_H
using namespace std;

//registro para receber as partículas
struct particula {
	char nome[20];
	position atual;
	char sistema;
	coordenada deslocamento;
	cores cor;
};

//função para ler as partículas
istream& operator>>(istream& is, particula& p);

#endif