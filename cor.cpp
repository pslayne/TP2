#include "cor.h"

istream& operator>>(istream& is, cores& c) {
	int num;
	is >> num;
	c = (cores)num;
	return is;
}