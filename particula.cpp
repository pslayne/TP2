#include "particula.h"

istream& operator>>(istream& is, particula& p) {
	is.getline(p.nome,20,':');
	is >> p.atual;
	is >> p.sistema;
	if (p.sistema == 'C')
		is >> p.deslocamento.cart;
	if (p.sistema == 'P')
		is >> p.deslocamento.pol;
	is >> p.cor;

	return is;
}

