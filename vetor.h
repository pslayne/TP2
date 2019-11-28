#include <iostream>
using namespace std;
#ifndef VETOR_H
#define VETOR_H

//registros das coordenadas
struct polar {
	float magnitude, angulo;
};

struct cartesiana {
	float x, y;
};

struct position {
	float x, y;
};

//uniãp polar ou cartesiana
union coordenada {
	polar pol;
	cartesiana cart;
};

//funções para ler os tipos novos
istream& operator>>(istream& is, position& p);
istream& operator>>(istream& is, polar& p);
istream& operator>>(istream& is, cartesiana& c);

//função deslocamento
position deslocamento(position ponto, char tipo, coordenada coord);
position desl_cart(position ponto, cartesiana deslocamento);
position desl_pol(position ponto, polar deslocamento);

//função colisão
bool colisao_horiz(position deslocamento);
bool colisao_vert(position deslocamento);

//funcao desvio
coordenada desvio(char tipo, coordenada coord, char direcao);

#endif

