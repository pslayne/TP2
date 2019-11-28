#include "particula.h"

//ler partícula
istream& operator>>(istream& is, particula& p) {
	//lê os caracteres até encontrar um ':'
	is.getline(p.nome,20,':');
	is >> p.atual;
	is >> p.sistema;
	//lê o vetor deslocamento em funçãos do sistema de coordenadas
	if (p.sistema == 'C')
		is >> p.deslocamento.cart;
	if (p.sistema == 'P')
		is >> p.deslocamento.pol;
	is >> p.cor;
	//descarta o \n que fica depois do nome
	is.ignore();

	return is;
}