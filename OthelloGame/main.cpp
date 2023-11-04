#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
#include <windows.h>
#include <Juego.h>

using namespace std;


int main() {
    // Declarar punteros para los nombres de los jugadores
    char* nombreJugador1 = nullptr;
    char* nombreJugador2 = nullptr;

    cout << "Nombre del Jugador 1: ";
    nombreJugador1 = new char[256];  // Asignar memoria dinámica para el nombre del Jugador 1
    cin >> nombreJugador1;

    cout << "Nombre del Jugador 2: ";
    nombreJugador2 = new char[256];  // Asignar memoria dinámica para el nombre del Jugador 2
    cin >> nombreJugador2;

    //Instanciar la clase Juego pasando los nombres de los jugadores
    Juego juego(nombreJugador1, nombreJugador2);

    // Llamar a los métodos de la clase Juego
    juego.jugar();
    juego.mostrarResultados();

    // Liberar la memoria dinámica después de su uso
    delete[] nombreJugador1;
    delete[] nombreJugador2;

    return 0;
    return 0;
}
