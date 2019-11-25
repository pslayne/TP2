#include <iostream>
using namespace std;

enum cores { vermelho, azul, branco, verde, amarelo };

istream& operator>>(istream& is, cores& c);