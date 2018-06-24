#include <conio.h>
#include "CMarkov.h"

using namespace std;

int main() {
	Climas * vClimas;
	vClimas = new Climas[30];
	short sizeClima = 0;

	System::Random r;

	for (short i = 0; i <= 80; i++)
		anadirClima(vClimas, sizeClima, Climas(r.Next((int)(nub), (int)(psol)+1)));
	sizeClima--;
	mostrarClima(vClimas, sizeClima);
	CMarkov hold;
	hold.calcularMatrizT(vClimas, sizeClima);
	system("Pause");
	return 0;
}