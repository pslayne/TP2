#include "vetor.h"
#include <cmath>

const float pi = 3.14159f;

//ler position (posição atual)
istream& operator>>(istream& is, position& p) {
	is >> p.x;
	is >> p.y;
	return is;
}

//ler coordenada polar
istream& operator>>(istream& is, polar& p) {
	is >> p.angulo;
	is >> p.magnitude;
	return is;
}

//ler coordenada cartesiana
istream& operator>>(istream& is, cartesiana& c) {
	is >> c.x;
	is >> c.y;
	return is;
}

//deslocamento cartesiano
position desl_cart(position ponto, cartesiana deslocamento) {
	float dx, dy;
	dx = ponto.x + deslocamento.x;
	dy = ponto.y - deslocamento.y;
	
	position resultado;
	resultado.x = dx;
	resultado.y = dy;

	return resultado;
}

//deslocamento polar
position desl_pol(position ponto, polar deslocamento) {
	float dx, dy;
	dx = deslocamento.magnitude * cos(deslocamento.angulo * pi / 180);
	dy = deslocamento.magnitude * sin(deslocamento.angulo * pi / 180);

	position resultado;
	resultado.x = ponto.x + dx;
	resultado.y = ponto.y - dy;
	
	return resultado;
}

//função que manda para deslocamento polar ou cartesiano
position deslocamento(position ponto, char tipo, coordenada coord)
{
	if (tipo == 'C') 
		return desl_cart(ponto, coord.cart);

	if (tipo == 'P') 
		return desl_pol(ponto, coord.pol);

}

//testa se colidiu nas paredes verticais
bool colisao_vert(position deslocamento) {
	if (deslocamento.x >= 800 || deslocamento.x <= 0)
		return true;
	else
		return false;
}

//testa se colidiu nas paredes horizontais
bool colisao_horiz(position deslocamento) {
	if (deslocamento.y >= 600 || deslocamento.y <= 0)
		return true;
	else
		return false;
}

//desvia as partículas que colidiram
coordenada desvio(char tipo, coordenada coord, char direcao)
{
	//cartesiana que colidiu nas paredes verticais
	if (tipo == 'C' && direcao == 'V') {
		coord.cart.x *= -1;
		
		return coord;
	}

	//cartesiana que colidiu nas paredes horizontais
	if (tipo == 'C' && direcao == 'H') {
		coord.cart.y *= -1;
		
		return coord;
	}

	//polar que colidiu nas paredes verticais
	if (tipo == 'P' && direcao == 'V') {
		float dx = coord.pol.magnitude * cos(coord.pol.angulo * pi / 180);
		dx *= -1;

		float dy = coord.pol.magnitude * sin(coord.pol.angulo * pi / 180);

		float novo_angulo = atan2(dy, dx) * (180 / pi);

		//se o angulo retornar negativo soma 360
		if (novo_angulo < 0)
			coord.pol.angulo = novo_angulo + 360;
		else
			coord.pol.angulo = novo_angulo;

		return coord;
	}

	//polar que colidiu nas paredes horizontais
	if (tipo == 'P' && direcao == 'H') {
		float dy = coord.pol.magnitude * sin(coord.pol.angulo * pi / 180);
		dy *= -1;

		float dx = coord.pol.magnitude * cos(coord.pol.angulo * pi / 180);

		float novo_angulo = atan2(dy, dx) * (180 / pi);

		//se o angulo retornar negativo soma 360
		if (novo_angulo < 0)
			coord.pol.angulo = novo_angulo + 360;
		else
			coord.pol.angulo = novo_angulo;

			return coord;
	}
}







