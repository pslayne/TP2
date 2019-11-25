#define _CRT_SECURE_NO_WARNINGS
#include "particula.h"
#include <random>
using namespace std;

//registro para armazenar o resultado das colis�es
struct collision {
	int quant_p, num_passos;
	//vetor est�tico de ponteiros para part�culas
	particula* particulas[10];
};

int main() {
	system("chcp 1252 > nul");

	//vetor est�tico de part�culas
	particula part[10];

	//armazena as 10 part�culas
	for (int a = 0; a < 10; a++) {
		cin >> part[a];
	}

	/*
	for (int teste = 0; teste < 10; teste++) {
		int x = part[teste].cor;
		cout << teste << " " << part[teste].nome << ":\n" << part[b].atual.x << " " << part[b].atual.y << " ";
		cout << part[teste].sistema << " ";
		cout << part[teste].deslocamento.cart.x << " " << part[teste].deslocamento.cart.y << " ";
		cout << x << endl;
	}*/

	//in�cio da simula��o
	cout << "\nSimula��o" << endl;
	cout << "---------" << endl;

	//vetor que armazena os resultados das colis�es
	collision colisoes[100];

	//la�o que preenche o vetor colisoes
	for(int h = 0, passo = 1; h < 100; passo++){
	cout << "#" << passo << ": ";

	//sorteio do n�mero de part�culas
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10);

	int tam = dist(mt);
	cout << " " << tam << " ( ";
	//vetor de ponteiros para part�culas do tamanho sorteado
	particula* movidas = new particula[tam];
	
	//la�o que armazena as part�culas que ser�o movidas
	for (int b = 0; b < tam; b++) {
		//sorteio das posi��es das particulas que ser�o movidas
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> dist(0, 9);

		int temp = dist(mt);
		movidas[b] = part[temp];
		cout << temp << " ";
	}

	cout << ") = ";

	//la�o que desloca as part�culas sorteadas
	for (int c = 0; c < tam; c++) {
		movidas[c].atual = deslocamento(movidas[c].atual, movidas[c].sistema, movidas[c].deslocamento);
		//cout << c << "\t x = " << movidas[c].atual.x << " y = " << movidas[c].atual.y << endl;
	}

	int quant_part_coli = 0;

	//la�o que testa as colis�es
	for (int d = 0, p = 0; d < tam; d++) {
		bool vertical = colisao_vert(movidas[d].atual);
		bool horizontal = colisao_horiz(movidas[d].atual);

		if (vertical || horizontal) {
			colisoes[h].particulas[p] = &movidas[d];
			p++;
			quant_part_coli++;
			
			//desvios
			if (vertical && horizontal) {
				char ch = 'V';
				movidas[d].deslocamento = desvio(movidas[d].sistema, movidas[d].deslocamento, ch);

				ch = 'H';
				movidas[d].deslocamento = desvio(movidas[d].sistema, movidas[d].deslocamento, ch);
			}
			else {
				if (vertical) {
					char ch = 'V';
					movidas[d].deslocamento = desvio(movidas[d].sistema, movidas[d].deslocamento, ch);
				}
				if (horizontal) {
					char ch = 'H';
					movidas[d].deslocamento = desvio(movidas[d].sistema, movidas[d].deslocamento, ch);
					//cout << d << "\t" << movidas[d].deslocamento.pol.magnitude << "\t" << movidas[d].deslocamento.pol.angulo << endl;
				}
			}
		}
	}
	cout << quant_part_coli << " ";

	//se houver colis�es preenche o vetor colisoes
	if (quant_part_coli) {
		colisoes[h].num_passos = passo;
		colisoes[h].quant_p = quant_part_coli;
		cout << "( ";
		for (int e = 0; e < colisoes[h].quant_p; e++) {
			int f;
			for (f = 0; colisoes[h].particulas[e]->nome[f] != (char)32; f++)
				continue;
			for (int g = f + 1; colisoes[h].particulas[e]->nome[g]; g++)
				cout << colisoes[h].particulas[e]->nome[g];
			cout << " ";
		}
		cout << ")" << endl;
		//incrementa o contador do la�o
		h++;
	}
	//se n�o pula uma linha
	else {
		cout << "\n";
	}
	//delete [] movidas;
	}

	//cout << "Lovelace \t x = " << part[1].atual.x << " y = " << part[1].atual.y << endl;
	cout << "\nResultados" << endl;
	cout << "----------" << endl;

	//n�mero de colis�es
	float soma = 0;
	for (int i = 0; i < 100; i++)
		soma += colisoes[i].quant_p;
	cout << "Colis�es: " << soma << endl;

	//m�dia de colis�es por passo
	int passos = colisoes[99].num_passos;
	cout << "Colis�es por passo: " << soma / passos << endl;
	
	//m�dia de passos entre as colis�es
	float som = 0.0f;
	for (int j = 0, k = 1; j < 99 && k < 100; j++, k++)
		som += colisoes[k].num_passos - colisoes[j].num_passos;
	cout << "M�dia de passos entre as colis�es: " << som/99 << endl;

	//colis�es por cor
	int verm = 0, az = 0, br = 0, ver = 0, am = 0;
	//percorre o vetor colisoes 
	for (int l = 0; l < 100; l++) {
		//percorre o vetor particulas (membro de colisoes)
		for (int m = 0; m < colisoes[l].quant_p; m++) {
			if (colisoes[l].particulas[m]->cor == vermelho)
				verm++;
			if (colisoes[l].particulas[m]->cor == azul)
				az++;
			if (colisoes[l].particulas[m]->cor == branco)
				br++;
			if (colisoes[l].particulas[m]->cor == verde)
				ver++;
			if (colisoes[l].particulas[m]->cor == amarelo)
				am++;
		}
	}
	cout << "Colis�es por cor: Vermelho(" << verm << ") Azul(" << az << ") Branco(" << br << ") Verde(" << ver << ") Amarelo(" << am << ")" << endl;
}