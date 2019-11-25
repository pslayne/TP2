#include <iostream> 
#include "vetor.h"
#include "cor.h"
using namespace std;

struct particula {
	char nome[20];
	position atual;
	char sistema;
	coordenada deslocamento;
	cores cor;
};

istream& operator>>(istream& is, particula& p);
