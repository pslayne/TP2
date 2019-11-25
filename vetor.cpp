#include "vetor.h"
#include <cmath>

istream& operator>>(istream& is, position& p) {
	is >> p.x;
	is >> p.y;
	return is;
}

istream& operator>>(istream& is, polar& p) {
	is >> p.magnitude;
	is >> p.angulo;
	return is;
}

istream& operator>>(istream& is, cartesiana& c) {
	is >> c.x;
	is >> c.y;
	return is;
}

position desl_cart(position ponto, cartesiana deslocamento) {
	float dx, dy;
	dx = ponto.x + deslocamento.x;
	dy = ponto.y + deslocamento.y;
	
	position resultado;
	resultado.x = dx;
	resultado.y = dy;

	return resultado;
}

position desl_pol(position ponto, polar deslocamento) {
	float dx, dy;
	dx = deslocamento.magnitude * cos(deslocamento.angulo);
	dy = deslocamento.magnitude * sin(deslocamento.angulo);

	position resultado;
	resultado.x = ponto.x + dx;
	resultado.y = ponto.y + dy;
	
	return resultado;
}

position deslocamento(position ponto, char tipo, coordenada coord)
{
	if (tipo == 'C') 
		return desl_cart(ponto, coord.cart);

	if (tipo == 'P') 
		return desl_pol(ponto, coord.pol);

}

bool colisao_horiz(position deslocamento) {
	if (deslocamento.x >= 800 || deslocamento.x <= 0)
		return true;
	else
		return false;
}

bool colisao_vert(position deslocamento) {
	if (deslocamento.y >= 600 || deslocamento.y <= 0)
		return true;
	else
		return false;
}

polar cartopol(cartesiana c) {
	polar p;
	float dx = c.x, dy = c.y;
	p.magnitude = sqrt(dx * dx + dy * dy);
	p.angulo = atan(dy / dx);
	return p;
}

float desvio_cart_vert(cartesiana cart) {
	return cart.y * -1;
}

float desvio_cart_horiz(cartesiana cart) {
	return cart.x * -1;
}

float desvio_pol_vert(polar pol) {
	float dy = pol.magnitude * sin(pol.angulo);
	return dy * -1;
}

float desvio_pol_horiz(polar pol) {
	float dx = pol.magnitude * cos(pol.angulo);
	return dx * -1;
}

coordenada desvio(char tipo, coordenada coord, char direcao)
{
	if (tipo == 'C' && direcao == 'V') {
		float dy = desvio_cart_vert(coord.cart);
		float dx = coord.cart.x;

		cartesiana desvio;
		desvio.x = dx;
		desvio.y = dy;
		
		coordenada novo_desl;
		novo_desl.cart = desvio;

		return novo_desl;
	}

	if (tipo == 'C' && direcao == 'H') {
		float dx = desvio_cart_horiz(coord.cart);
		float dy = coord.cart.y;

		cartesiana desvio;
		desvio.x = dx;
		desvio.y = dy;

		coordenada novo_desl;
		novo_desl.cart = desvio;

		return novo_desl;
	}

	if (tipo == 'P' && direcao == 'V') {
		float dy = desvio_pol_vert(coord.pol);
		float dx = coord.pol.magnitude * cos(coord.pol.angulo);

		coordenada novo_desl;
		novo_desl.cart.x = dx;
		novo_desl.cart.y = dy;

		polar desvio = cartopol(novo_desl.cart);

		novo_desl.pol = desvio;

		return novo_desl;
	}

	if (tipo == 'P' && direcao == 'H') {
		float dx = desvio_pol_horiz(coord.pol);
		float dy = coord.pol.magnitude * sin(coord.pol.angulo);

		coordenada novo_desl;
		novo_desl.cart.x = dx;
		novo_desl.cart.y = dy;

		polar desvio = cartopol(novo_desl.cart);

		novo_desl.pol = desvio;

		return novo_desl;
	}
}








