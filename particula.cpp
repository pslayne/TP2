#include "particula.h"

//ler part�cula
istream& operator>>(istream& is, particula& p) {
	//l� os caracteres at� encontrar um ':'
	is.getline(p.nome,20,':');
	is >> p.atual;
	is >> p.sistema;
	//l� o vetor deslocamento em fun��os do sistema de coordenadas
	if (p.sistema == 'C')
		is >> p.deslocamento.cart;
	if (p.sistema == 'P')
		is >> p.deslocamento.pol;
	is >> p.cor;
	//descarta o \n que fica depois do nome
	is.ignore();

	return is;
}