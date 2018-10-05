#include <iostream>
//markov incompleto

using namespace std;
enum Climas {nub, pnub, sol, psol};
char *NClimas[] = { "Nublado", "Parcialmente Nublado", "Soleado", "Parcialmente Soleado" };


void anadirClima(Climas * &vector, short &n, Climas cDay) {
	if (n < 30) 
		vector[n] = cDay;
	else if (n<=80) {
		Climas *temp = new Climas[n];
		for (short i = 0; i < n-1; i++)
			temp[i] = vector[i];
		
		temp[n-1] = cDay;
		delete[] vector;

		vector = temp;
	}
	else 
		return;
	cout << vector[n-1];
	n++;
	return;
}

void mostrarClima(Climas *vector, short n) {
	for (short i = 0; i < n; i++)
		cout << "Dia " << i + 1 << " " << NClimas[int(vector[i])] << endl;
	return;
}
