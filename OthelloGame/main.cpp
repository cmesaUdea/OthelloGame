#include <iostream>
#include <fstream>
#include <ctime>
//#include <vector>
#include <limits>
#include <windows.h>
#include <Juego.h>

using namespace std;


int main() {
    string nombreJugador1, nombreJugador2;
    cout << "Nombre del Jugador 1: ";
    cin >> nombreJugador1;
    cout << "Nombre del Jugador 2: ";
    cin >> nombreJugador2;

    Juego juego(nombreJugador1, nombreJugador2);
    juego.jugar();
    juego.mostrarResultados();

    return 0;
}
