#include "Header.h"

//Terminaste la matriz de Transicion

class CMarkov
{
private:
	float matrizT[4][4], matrizPn[4]; //Declaramos el atributos matriz Transicion y matris Composicion actual
	float matrizP0[4]; //matriz composición inicial
	const short matrizI[4][4] = { //matriz identidad Rango 4
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 },
	};
	const short matrizN[4][1] = { {0},{0},{0},{0} }; //Matriz nula

public:
	CMarkov();

	void calcularMatrizT(Climas * vClimas, short n);
	void calcularMatrizP0(Climas * vClimas, short n);
	void calculaMatrizPn(); 
};

CMarkov::CMarkov(){
	for (short i = 0; i < 4; i++) {
		matrizP0[i] = 0;
		matrizPn[i]= 0;
	}
}


void CMarkov::calcularMatrizT(Climas * vClimas, short n) { //Matriz de composicion
	short cntCambios[4][4] = { { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 } };
	short cntCambioT[] = { 0,0,0,0 };

	for (short i = 1; i < n; i++) {
		cntCambios[int(vClimas[i - 1])][int(vClimas[i])]++;
		cntCambioT[vClimas[i]]++;
	}

	for (short i = 0; i < 4; i++){
		for (short j = 0; j < 4; j++) {
			cout << "Casos " << i << j << ": " << cntCambios[i][j] <<" - "<< cntCambios[i][j]/float(cntCambioT[i]) << endl;
			this->matrizT[i][j] = cntCambios[i][j] / float(cntCambioT[i]);
		}
		cout << cntCambioT[i] << endl;
	}
	return;

	this->matrizP0[vClimas[n - 1]] = 1;
}

void CMarkov::calcularMatrizP0(Climas * vClimas, short n) {
	
	
}
