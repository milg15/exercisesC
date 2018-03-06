#include <Windows.h>
#include <MMSystem.h>
#include <chrono>
#include "mapas.h"
#include "keyboard.h"

using namespace chrono;

// libreria <iostream>, using namespace std y System declarada en mapas.h
// libreria <conio.h> declarada en keyboard.h

//Posicion Inicial del Jugador
#define POSXJUG 11
#define POSYJUG 7

//Mostrar el Menu
const char *MenuOpciones[] = { "NUEVO JUEGO", "INSTRUCCIONES", "SONIDO", "SALIR" }; // opciones del menu
const short n_opciones = 4; //numero de opciones del menu

//Inicio y movimiento del juego 
bool Juego(Personaje &Jugador, bool sound); 

//Funciones de Movimiento de Jugador 
void cambioMapa(short n, Personaje &J, Personaje * &E, short &nEnemigos); // Coloca mapa del sig nivel y al jugador es la poscion inicial

//Pantallas y menu

short MenuInteractivo(const char * opciones[], const short n);	
bool MenuPrincipal(bool &sound, short &crrS);
void bannerFinal(bool b, short puntaje);		
void Sonidos(short s);		
void MostrarInstrucciones(); //Muestra las instrucciones del juego

int main() {
	bool state, win;
	Console::CursorVisible = false;
	short crrSong = 0;

	while (true) {
		//Muestra el menu principal
		Sonidos(crrSong);

		bool sound = true;
		state = MenuPrincipal(sound, crrSong);
		if (!state)
			break;

		//Se crea el personaje 
		Personaje Jugador;
		crearPersonaje(Jugador, POSXJUG, POSYJUG, 100, 1, 152);
		
		//Inicia el Juego
		win = Juego(Jugador, sound);

		if (win) {
			bannerFinal(true, 5);
		}
		else
			bannerFinal(false, 5);
	}
	return 0;
}

short MenuInteractivo(const char * opciones[], const short n) {
	short seleccion = 1;
	short key;
	bool repeat = true;

	const short x = 15;
	const short y = 8;
	system("cls");

	Console::ForegroundColor = ConsoleColor::Blue; //Color del menu

	//Imprimir el titulo
	Console::SetCursorPosition(2, 2);
	cout << "    _/_/_/    _/_/_/_/  _/_/_/    _/_/_/_/_/  _/_/_/_/  _/_/_/    _/    _/  ";
	Console::SetCursorPosition(2, 3);
	cout << "   _/    _/  _/        _/    _/        _/    _/        _/    _/  _/  _/      ";
	Console::SetCursorPosition(2, 4);
	cout << "  _/_/_/    _/_/_/    _/_/_/        _/      _/_/_/    _/_/_/    _/_/         ";
	Console::SetCursorPosition(2, 5);
	cout << " _/    _/  _/        _/    _/    _/        _/        _/    _/  _/  _/        ";
	Console::SetCursorPosition(2, 6);
	cout << "_/_/_/    _/_/_/_/  _/    _/  _/_/_/_/_/  _/_/_/_/  _/    _/  _/    _/    ";

	//Muestra las opciones del menu
	for (short i = 1; i <= n; i++) {
		Console::SetCursorPosition(x + 5, y + i);
		cout << i << ". " << MenuOpciones[i - 1];
	}

	Console::SetCursorPosition(x, 19);
	cout << "Creditos: ELVIA ARTEAGA - MARIA LOPEZ ";

	while (repeat) {
		//se imprime flecha de seleccion
		Console::SetCursorPosition(x, y + seleccion); cout << "==>";
		
		//Lee la accion del teclado
		short pastS = seleccion;
		do {
			key = keyboardActions();
		} while (key != KB_UP && key != KB_DOWN && key != KB_ENTER);

		switch (key) {
		case KB_UP: {
			if (seleccion == 1)
				seleccion = n;
			else
				seleccion--;
			break;

		}
		case KB_DOWN: {
			if (seleccion == n)
				seleccion = 1;
			else
				seleccion++;
			break;
		}
		case KB_ENTER:
			repeat = false;
		}

		//Elimina la poscion de la flecha anterior
		Console::SetCursorPosition(x, y + pastS); cout << "   ";
	}
	return seleccion;
}

bool MenuPrincipal(bool &sound, short &crrS) {
	while (true) {
		//Titulo del menu;
		system("cls");
		short op = MenuInteractivo(MenuOpciones, n_opciones);
		if (op == 1) {
			//Inicia el juego enviando verdadero
			return true;
		}
		else if (op == 2) {
			//Muestra las intrucciones
			system("cls");
			MostrarInstrucciones();
			while (keyboardActions() != KB_ENTER);

		}
		else if (op == 3) {
			//Do Something with sound
			if (crrS == 0 || crrS == 1) {
				crrS++;
				if (crrS>1)
					sound = false; 
			}
			else {
				crrS = 0;
				sound = true;
			};
			Sonidos(crrS);
		}
		else if (op == 4) {
			//Salir del Juego
			return false;
		}
	}
	return true;
}

void MostrarInstrucciones() {
	short movx = 11, movy = 2;
	imprimirMarco();
	Console::SetCursorPosition(6 + movx, 9 + movy);
	cout << "El proposito de este juego es completar 8 mapas";
	Console::SetCursorPosition(6 + movx, 10 + movy);
	cout << "para ello el jugador cuenta con 5 vidas y 4 min.";
	Console::SetCursorPosition(5 + movx, 12 + movy);
	cout << "El movimiento del jugador es mediante las teclas";
	Console::SetCursorPosition(17 + movx, 13 + movy);
	cout << "direccionales del teclado";
	Console::SetCursorPosition(6 + movx, 15 + movy);
	cout << "El jugador pierde vida cuando toca la pared del";
	Console::SetCursorPosition(17 + movx, 16 + movy);
	cout << "laberinto o algun enemigo";
	Console::SetCursorPosition(6 + movx, 18 + movy);
	cout << "El jugador gana cuando logra atrevesar todos ";
	Console::SetCursorPosition(19 + movx, 19 + movy);
	cout << "los mapas.";
	Console::SetCursorPosition(7 + movx, 20 + movy);
	cout << "El jugador pierde cuando se queda sin vidas";
	Console::SetCursorPosition(16 + movx, 21 + movy);
	cout << "o se finalizan los 5 minutos";
}

//LA CARPETA Sounds se debe encontrar en la misma ubicacion que el archivo ejecutable
void Sonidos(short s) {
	if (s == 0)
		PlaySound(TEXT("Sounds\\Stressed_Out.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	else if (s == 1)
		PlaySound(TEXT("Sounds\\Digital_Native.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	else if (s == 10)
		PlaySound(TEXT("Sounds\\sfx_deathscream.wav"), NULL, SND_ASYNC | SND_FILENAME);
	else if (s == 11)
		PlaySound(TEXT("Sounds\\sfx_footsteps.wav"), NULL, SND_ASYNC | SND_FILENAME);
	else if (s == 12)
		PlaySound(TEXT("Sounds\\sfx_portal.wav"), NULL, SND_ASYNC | SND_FILENAME);
	else if(s==13)
		PlaySound(TEXT("Sounds\\sfx_deathscream2.wav"), NULL, SND_ASYNC | SND_FILENAME);
	else if (s==20)
		PlaySound(TEXT("Sounds\\victory.wav"), NULL, SND_ASYNC | SND_FILENAME);
	else if (s==21)
		PlaySound(TEXT("Sounds\\game_over.wav"), NULL, SND_ASYNC | SND_FILENAME);

	else
		PlaySound(NULL, NULL, 0);

	return;
}

void bannerFinal(bool b, short puntanje) {
	system("cls");
	Console::ForegroundColor = ConsoleColor::Red;
	if (b) {
		cout << endl << endl << endl << endl << endl;;
		cout << "		`I8,        8        ,8I   88  888b      88  88  88 " << endl;
		cout << "		`8b       d8b       d8'   88  8888b     88  88  88 	" << endl;
		cout << "		`8,     ,8''8,    , 8'   88  88 `8b    88  88  88  	" << endl;
		cout << "		`Y8     8P Y8     8P    88  88  `8b   88  88  88  	" << endl;
		cout << "		`8b   d8' `8b   d8'    88  88   `8b  88  88  88  	" << endl;
		cout << "		`8a a8'   `8a a8'     88  88    `8b 88  ''  ''		" << endl;
		cout << "		`8a8'     `8a8'      88  88     `8888  aa  aa		" << endl;
		cout << "		`8'       `8'       88  88      `888  88  88		" << endl;
		Sonidos(20);

	}
	else {
		cout << endl << endl << endl;
		cout << " 	  ,ad8888ba,          db         88b           d88  88888888888 " << endl;
		cout << "	 d8''    `'8b        d88b        888b         d888  88          " << endl;
		cout << "	d8'                 d8'`8b       88`8b       d8'88  88          " << endl;
		cout << "	88                 d8'  `8b      88 `8b     d8' 88  88aaaaa     " << endl;
		cout << "	88      88888     d8YaaaaY8b     88  `8b   d8'  88  88'''''     " << endl;
		cout << "	Y8,        88    d8''''''''8b    88   `8b d8'   88  88          " << endl;
		cout << "	 Y8a.    .a88   d8'        `8b   88    `888'    88  88          " << endl;
		cout << "	  `'Y88888P'   d8'          `8b  88     `8'     88  88888888888 " << endl << endl;
		cout << " 	  ,ad8888ba,    8b           d8  88888888888  88888888ba  " << endl;
		cout << " 	 d8''    `'8b   `8b         d8'  88           88      '8b " << endl;
		cout << " 	d8'        `8b   `8b       d8'   88           88      ,8P " << endl;
		cout << " 	88          88    `8b     d8'    88aaaaa      88aaaaaa8P' " << endl;
		cout << " 	88          88     `8b   d8'     88'''''      88''''88'   " << endl;
		cout << " 	Y8,        ,8P      `8b d8'      88           88    `8b   " << endl;
		cout << " 	 Y8a.    .a8P        `888'       88           88     `8b  " << endl;
		cout << " 	  ''Y8888Y''          `8'        88888888888  88      `8b " << endl;
		Sonidos(21);
	}
	Sleep(5000);
	system("Pause");
}

void cambioMapa(short n, Personaje &J, Personaje * &E, short &nEnemigos) {
	system("cls");
	Console::SetCursorPosition(1, 2);
	Console::ForegroundColor = ConsoleColor::White;
	cout << "NIVEL " << n << endl;
	Console::SetCursorPosition(1, 4);
	cout << "PUNTAJE:";
	Console::SetCursorPosition(2, 5);
	cout << J.pnt << "  ";
	Console::SetCursorPosition(1, 6);
	cout << "TIEMPO";
	
	copiarMapa(n);

	if (n < 5)
		nEnemigos = n;
	else
		nEnemigos = 5;

	E = new Personaje[nEnemigos];
	
	//Se muestra el mapa
	mostrarMapa(E);

	Console::ForegroundColor = ConsoleColor::White;
	Console::SetCursorPosition(1, 1);
	cout << "VIDAS: " << J.vidas;
	dibujarJugador(J);

	for (short i = 0; i < nEnemigos && E[i].x != 0; i++)
		dibujarEnemigo(E[i]);

	return;

}

bool Juego(Personaje &Jugador, bool sound) {
	Random r;
	short nivel = 1, key, tempx, tempy, nEm;
	short *dx, *dyB, *dispara;
	bool wall = true;

	//Declaracion de enemigos
	Personaje *Enemigos, *Balas;
	cambioMapa(nivel, Jugador, Enemigos, nEm);
	dx = new short[nEm];
	dyB = new short[nEm];
	inicializarArreglos(nEm, Enemigos, Balas, dispara, dx, dyB);
	
	// Disparo del Jugador
	bool shot = false, control = false;
	short dyJ = 0, xBalaJ, yBalaJ;

	short sec, min;
	//Inicia el tiempo
	time_point<system_clock> start;
	start = system_clock::now(); 
	while (true) {
		//Temporizador
		sec = duration_cast<seconds>(system_clock::now() - start).count();
		min = duration_cast<minutes>(system_clock::now() - start).count();

		if (min == 4)
			Console::ForegroundColor = ConsoleColor::Red;
		else
			Console::ForegroundColor = ConsoleColor::White;

		//Si se llegan a los 5 min se acaba el juego
		if (min >= 5) {
			delete[] Enemigos;
			delete[] dx;
			return false;
		}
		Console::SetCursorPosition(2, 7);
		if (sec % 60 < 10)
			cout << 0 << min << ":" << 0 << sec % 60;
		else
			cout << 0 << min << ":" << sec % 60;

		//Movimiento del enemigo y BALA
		for (short i = 0; i < nEm; i++) {
			//Si la vida del enemigo es mayor que 0 se muetra el enemigo
			if (Enemigos[i].vidas>0) {
				//genera posicion random de disparo
				dispara[i] = r.Next(12, COLUMNAS + 9);

				//Movimiento del enemigo
				if (moverEnemigo(Enemigos[i].x, Enemigos[i].y, dx[i])) {
					eliminarRastro(Enemigos[i].x, Enemigos[i].y);
					Enemigos[i].x += dx[i];
					dibujarEnemigo(Enemigos[i]);
				}

				//Movimiento de la balas
				if (Balas[i].y < FILAS && Balas[i].y > 3 &&
					mapaActual[Balas[i].y - 2][Balas[i].x - 10] == 0) {
					eliminarBala(Balas[i].x, Balas[i].y);
					Balas[i].y += dyB[i];
				}
				if (Enemigos[i].x == dispara[i]) {
					Balas[i].x = Enemigos[i].x;
					Balas[i].y = Enemigos[i].y + dyB[i];
				}

				if (mapaActual[Balas[i].y - 2][Balas[i].x - 10] == 0) {
					dibujarBala(Balas[i].x, Balas[i].y, false);
					if (Balas[i].y >= FILAS || Balas[i].y <= 3)
						eliminarBala(Balas[i].x, Balas[i].y);
				}
			}
		}

		if (_kbhit()) {
			key = keyboardActions();
			tempx = Jugador.x, tempy = Jugador.y;

			//verifica que no haya un disparo en el momento
			if (!shot)
				control = true;

			//Controlar el movimiento de las teclas
			switch (key) {
			case KB_UP: {	Jugador.y--; break; }
			case KB_LEFT: {	Jugador.x--; break; }
			case KB_DOWN: {	Jugador.y++; break; }
			case KB_RIGHT: { Jugador.x++; break; }
			case LOWER_SHOT: { shot = true; if (control) dyJ = 1; break; }
			case UPPER_SHOT: { shot = true; if (control) dyJ = -1; break; }
			}
			
			//Inicializa un disparo del jugador
			if (shot && control && (key == LOWER_SHOT || key == UPPER_SHOT)) {
				xBalaJ = Jugador.x;
				yBalaJ = Jugador.y + dyJ;
				control = false;
			}

			Console::ForegroundColor = ConsoleColor::White;
			//Verificar si esta sobre una vida o un puntaje.
			if (mapaActual[Jugador.y - 2][Jugador.x - 10] == 4) {
				mapaActual[Jugador.y - 2][Jugador.x - 10] = 0;
				Jugador.pnt += 100;
				Console::SetCursorPosition(2, 5);
				cout << Jugador.pnt << "  ";
			}
			else if (mapaActual[Jugador.y - 1][Jugador.x - 10] == 4) {
				mapaActual[Jugador.y - 1][Jugador.x - 10] = 0;
				Jugador.pnt += 100;
				Console::SetCursorPosition(2, 5);
				cout << Jugador.pnt << "  ";
			}
			else if (mapaActual[Jugador.y - 2][Jugador.x - 10] == 5) {
				mapaActual[Jugador.y - 2][Jugador.x - 10] = 0;
				Jugador.vidas++;

				// Se muestra en pantalla la vida actualizada
				Console::SetCursorPosition(1, 1);
				cout << "VIDAS: " << Jugador.vidas;
			}
			else if (mapaActual[Jugador.y - 1][Jugador.x - 10] == 5) {
				mapaActual[Jugador.y - 1][Jugador.x - 10] = 0;
				Jugador.vidas++;

				// Se muestra en pantalla la vida actualizada
				Console::SetCursorPosition(1, 1);
				cout << "VIDAS: " << Jugador.vidas;
			}

			//Verificar si la posicion a la que se desea mover el jugador es valida
			if (mapaActual[Jugador.y - 2][Jugador.x - 10] == 0 && mapaActual[Jugador.y - 1][Jugador.x - 10] == 0) {
				if(key!=-1)
					wall = false;

				eliminarRastro(tempx, tempy);
				if (!sound)	Sonidos(11);
			}
			else{
				//Pierde una vida el jugador si esta tocando una tecla diferente
				if (!wall) {
					Jugador.vidas--;

					//Se muestra en pantalla la vida actualizada
					Console::SetCursorPosition(1, 1);
					cout << "VIDAS: " << Jugador.vidas << " ";
					if (!sound)	Sonidos(10);
					wall = true;
				}
				//Se reasigna el valor anterior a la posxy del jugador
				Jugador.x = tempx; Jugador.y = tempy;
			}

			//Para cambiar al siguiente mapa
			if (Jugador.x - 10 == COLUMNAS - 1 || Jugador.x - 10 == 0 || Jugador.y - 2 == 0 || Jugador.y - 1 == FILAS - 1) {
				nivel++;
				
				eliminarArreglos(Enemigos, Balas, dx, dyB, dispara);
				//Termina el Juego ha llegado al ultimo nivel
				if (nivel == 9)
					return true;

				//Cambia la posicion del jugador acorde al siguiente mapa
				if (Jugador.x - 10 == COLUMNAS - 1)
					Jugador.x -= COLUMNAS - 2;
				else if (Jugador.y - 2 == 0)
					Jugador.y += FILAS - 3;
				else if (Jugador.x - 10 == 0)
					Jugador.x += COLUMNAS - 2;
				else
					Jugador.y -= FILAS - 3;

				//Se llama la funcion cambio de mapa
				cambioMapa(nivel, Jugador, Enemigos, nEm);

				inicializarArreglos(nEm, Enemigos, Balas, dispara, dx, dyB);

				if (!sound)	Sonidos(12);
				Sleep(600);

			}
		}
		
		//Dibuja al jugador
		dibujarJugador(Jugador);

		//Movimiento de la bala del jugador
		if (shot) {			
			if (yBalaJ < FILAS && yBalaJ > 3 &&
				mapaActual[yBalaJ - 2][xBalaJ - 10] == 0) {
				eliminarBala(xBalaJ, yBalaJ);
				yBalaJ+= dyJ;
			}
			else 
				shot = false;

			if (mapaActual[yBalaJ - 2][xBalaJ - 10] == 0)
				dibujarBala(xBalaJ, yBalaJ, true);
			if (mapaActual[yBalaJ - 2][xBalaJ - 10] == 0 && !shot)
				eliminarBala(xBalaJ, yBalaJ);

		}

		for (short i = 0; i < nEm; i++) {
			//Si la bala del jugador toca al enemigo muere
			if ((xBalaJ == Enemigos[i].x && ((yBalaJ == Enemigos[i].y) || yBalaJ == Enemigos[i].y + 1))) {
				eliminarRastro(Enemigos[i].x, Enemigos[i].y);
				Enemigos[i].vidas--;
				Enemigos[i].x = Enemigos[i].y = -1;
				if (Balas[i].x != -1 && Balas[i].y != -1) {
					if (Balas[i].y < FILAS && Balas[i].y > 3 &&
						mapaActual[Balas[i].y - 2][Balas[i].x - 10] == 0)
						eliminarBala(Balas[i].x, Balas[i].y);
					else
						Balas[i].x = Balas[i].y = -1;
				}
			}
			// Si el personaje toca al enemigo pierde vida
			if ((Jugador.x == Enemigos[i].x && Jugador.y == Enemigos[i].y)	|| (Jugador.x == Enemigos[i].x && Jugador.y + 1 == Enemigos[i].y)
				|| (Jugador.x == Enemigos[i].x && Jugador.y + 1 == Enemigos[i].y + 1) || (Jugador.x == Enemigos[i].x && Jugador.y == Enemigos[i].y + 1)){
				Jugador.vidas--;
				if (!sound)	Sonidos(13);

				// Se muestra en pantalla la vida actualizada
				Console::SetCursorPosition(1, 1);
				Console::ForegroundColor = ConsoleColor::White;
				cout << "VIDAS: " << Jugador.vidas;

			}

			//Si la bala toca al jugador pierde vida
			if ((Jugador.x == Balas[i].x && Jugador.y == Balas[i].y) || (Jugador.x == Balas[i].x && Jugador.y + 1 == Balas[i].y)){
				Jugador.vidas--;
				if (!sound)	Sonidos(13);
				eliminarBala(Balas[i].x, Balas[i].y);
				Balas[i].x = -1; 
				Balas[i].y = -1;

				// Se muestra en pantalla la vida actualizada
				Console::SetCursorPosition(1, 1);
				Console::ForegroundColor = ConsoleColor::White;
				cout << "VIDAS: " << Jugador.vidas;
			}
		}

		//Si se han acabado las vidas termina el juego
		if (Jugador.vidas <= 0) {
			eliminarArreglos(Enemigos, Balas, dx, dyB, dispara);

			return false;
		}

		Sleep(40);
	}
}