#include <iostream>
using namespace std;

struct polar {
	float magnitude, angulo;
};

struct cartesiana {
	float x, y;
};

union coordenada {
	polar pol;
	cartesiana cart;
};

struct position {
	float x, y;
};

istream& operator>>(istream& is, position& p);
istream& operator>>(istream& is, polar& p);
istream& operator>>(istream& is, cartesiana& c);
istream& operator>>(istream& is, coordenada& c);

//função deslocamento
position deslocamento(position ponto, char tipo, coordenada coord);
position desl_cart(position ponto, cartesiana deslocamento);
position desl_pol(position ponto, polar deslocamento);

//função colisão
bool colisao_horiz(position deslocamento);
bool colisao_vert(position deslocamento);

//transforma coordenada polar em cartesiana
polar cartopol(cartesiana c);

//funcao desvio
coordenada desvio(char tipo, coordenada coord, char direcao);
float desvio_cart_vert(cartesiana cart);
float desvio_cart_horiz(cartesiana cart);
float desvio_pol_vert(polar pol);
float desvio_pol_horiz(polar pol);
