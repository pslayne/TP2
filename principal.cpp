#include "particula.h"
#include <random>
using namespace std;

//registro para armazenar o resultado das colisões
struct collision {
	int quant_p, num_passos;
	//vetor estático de ponteiros para partículas
	particula* particulas[10];
};

//função que separa a string para mostrar apenas o sobrenome
void separador(char[]);

int main() {
	//altera o código de página
	system("chcp 1252 > nul");

	//vetor estático de partículas
	particula part[10];

	//armazena as 10 partículas
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

	//início da simulação
	cout << "\nSimulação" << endl;
	cout << "---------" << endl;

	//vetor que armazena os resultados das colisões
	collision colisoes[100];

	//laço que preenche o vetor colisoes
	for(int h = 0, passo = 1; h < 100; passo++){
	cout << "#" << passo << ": ";

	//sorteio do número de partículas
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10);

	int tam = dist(mt);
	cout << " " << tam << " ( ";
	//vetor de ponteiros para partículas do tamanho sorteado
	particula** movidas = new particula*[tam];
	
	//laço que armazena as partículas que serão movidas
	for (int b = 0; b < tam; b++) {
		//sorteio das posições das particulas que serão movidas
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> dist(0, 9);

		int temp = dist(mt);
		movidas[b] = &part[temp];
		cout << temp << " ";
	}

	cout << ") = ";

	//laço que desloca as partículas sorteadas
	for (int c = 0; c < tam; c++) {
		movidas[c]->atual = deslocamento(movidas[c]->atual, movidas[c]->sistema, movidas[c]->deslocamento);
		//cout << "\n" << c << "\t x = " << movidas[c].atual.x << " y = " << movidas[c].atual.y << endl;
	}

	//vai armazenar a quantidade de partículas que colidiram
	int quant_part_coli = 0;

	//laço que testa as colisões
	for (int d = 0, p = 0; d < tam; d++) {
		bool vertical = colisao_vert(movidas[d]->atual);
		bool horizontal = colisao_horiz(movidas[d]->atual);

		if (vertical || horizontal) {
			//armazena as partículas que colidiram no vetor particula do vetor colisoes
			colisoes[h].particulas[p] = movidas[d];
			//incrementa a variável do índice de particulas
			p++;
			//incrementa o número total de partículas que colidiram
			quant_part_coli++;
			
			//desvios
			if (vertical && horizontal) {
				//se colidiu nas duas direções, inverte as duas partes da coordenada
				
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

	//se houver colisões preenche o vetor colisoes
	if (quant_part_coli) {
		colisoes[h].num_passos = passo;
		colisoes[h].quant_p = quant_part_coli;
		cout << "( ";
		for (int e = 0; e < colisoes[h].quant_p; e++) {
			separador(colisoes[h].particulas[e]->nome);
		}
		cout << ")" << endl;
		//e incrementa o contador do primeiro laço
		h++;
	}
	//se não pula uma linha
	else {
		cout << "\n";
	}
	//libera a memória alocada para o vetor dinâmico de ponteiros
	delete [] movidas;
	}

	cout << "\nResultados" << endl;
	cout << "----------" << endl;

	//número de colisões
	float soma = 0;
	for (int i = 0; i < 100; i++)
		soma += colisoes[i].quant_p;
	cout << "Colisões: " << soma << endl;

	//média de colisões por passo
	int passos = colisoes[99].num_passos;
	cout << "Colisões por passo: " << soma / passos << endl;
	
	//média de passos entre as colisões
	float som = 0.0f;
	//subtrai os números de passos
	for (int j = 0, k = 1; j < 99 && k < 100; j++, k++)
		som += colisoes[k].num_passos - colisoes[j].num_passos;
	//divide por 99 porque é o número de espaços entre 100 números
	cout << "Média de passos entre as colisões: " << som/99 << endl;

	//colisões por cor
	int verm = 0, az = 0, br = 0, ver = 0, am = 0;
	//percorre o vetor colisoes 
	for (int l = 0; l < 100; l++) {
		//percorre o vetor particulas (membro de colisoes)
		for (int m = 0; m < colisoes[l].quant_p; m++) {
			//soma nas variáveis de cada cor
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
	cout << "Colisões por cor: Vermelho(" << verm << ") Azul(" << az << ") Branco(" << br << ") Verde(" << ver << ") Amarelo(" << am << ")" << endl;
}

void separador(char nome[]) {
		int f;
		//percorre o vetor até encontrar um espaço (código 32)
		for (f = 0; nome[f] != (char)32; f++)
			continue;
		//percorre o vetor a partir do caracter imediatamente depois do espaço
		for (int g = f + 1; nome[g]; g++)
			cout << nome[g];
		cout << " ";
	}
