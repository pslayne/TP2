#include "particula.h"
#include <random>
using namespace std;

//registro para armazenar o resultado das colis�es
struct collision {
	int quant_p, num_passos;
	//vetor est�tico de ponteiros para part�culas
	particula* particulas[10];
};

//fun��o que separa a string para mostrar apenas o sobrenome
void separador(char[]);

int main() {
	//altera o c�digo de p�gina
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
	particula** movidas = new particula*[tam];
	
	//la�o que armazena as part�culas que ser�o movidas
	for (int b = 0; b < tam; b++) {
		//sorteio das posi��es das particulas que ser�o movidas
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> dist(0, 9);

		int temp = dist(mt);
		movidas[b] = &part[temp];
		cout << temp << " ";
	}

	cout << ") = ";

	//la�o que desloca as part�culas sorteadas
	for (int c = 0; c < tam; c++) {
		movidas[c]->atual = deslocamento(movidas[c]->atual, movidas[c]->sistema, movidas[c]->deslocamento);
		//cout << "\n" << c << "\t x = " << movidas[c].atual.x << " y = " << movidas[c].atual.y << endl;
	}

	//vai armazenar a quantidade de part�culas que colidiram
	int quant_part_coli = 0;

	//la�o que testa as colis�es
	for (int d = 0, p = 0; d < tam; d++) {
		bool vertical = colisao_vert(movidas[d]->atual);
		bool horizontal = colisao_horiz(movidas[d]->atual);

		if (vertical || horizontal) {
			//armazena as part�culas que colidiram no vetor particula do vetor colisoes
			colisoes[h].particulas[p] = movidas[d];
			//incrementa a vari�vel do �ndice de particulas
			p++;
			//incrementa o n�mero total de part�culas que colidiram
			quant_part_coli++;
			
			//desvios
			if (vertical && horizontal) {
				//se colidiu nas duas dire��es, inverte as duas partes da coordenada
				
				char ch = 'V';
				movidas[d]->deslocamento = desvio(movidas[d]->sistema, movidas[d]->deslocamento, ch);

				ch = 'H';
				movidas[d]->deslocamento = desvio(movidas[d]->sistema, movidas[d]->deslocamento, ch);
			}
			else {
				//se colidiu em apenas uma, inverte somente a que colidiu
				if (vertical) {
					char ch = 'V';
					movidas[d]->deslocamento = desvio(movidas[d]->sistema, movidas[d]->deslocamento, ch);
				}
				if (horizontal) {
					char ch = 'H';
					movidas[d]->deslocamento = desvio(movidas[d]->sistema, movidas[d]->deslocamento, ch);
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
			separador(colisoes[h].particulas[e]->nome);
		}
		cout << ")" << endl;
		//e incrementa o contador do primeiro la�o
		h++;
	}
	//se n�o pula uma linha
	else {
		cout << "\n";
	}
	//libera a mem�ria alocada para o vetor din�mico de ponteiros
	delete [] movidas;
	}

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
	//subtrai os n�meros de passos
	for (int j = 0, k = 1; j < 99 && k < 100; j++, k++)
		som += colisoes[k].num_passos - colisoes[j].num_passos;
	//divide por 99 porque � o n�mero de espa�os entre 100 n�meros
	cout << "M�dia de passos entre as colis�es: " << som/99 << endl;

	//colis�es por cor
	int verm = 0, az = 0, br = 0, ver = 0, am = 0;
	//percorre o vetor colisoes 
	for (int l = 0; l < 100; l++) {
		//percorre o vetor particulas (membro de colisoes)
		for (int m = 0; m < colisoes[l].quant_p; m++) {
			//soma nas vari�veis de cada cor
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

void separador(char nome[]) {
		int f;
		//percorre o vetor at� encontrar um espa�o (c�digo 32)
		for (f = 0; nome[f] != (char)32; f++)
			continue;
		//percorre o vetor a partir do caracter imediatamente depois do espa�o
		for (int g = f + 1; nome[g]; g++)
			cout << nome[g];
		cout << " ";
	}
