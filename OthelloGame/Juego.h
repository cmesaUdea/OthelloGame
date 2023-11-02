#ifndef JUEGO_H
#define JUEGO_H

#include <string>

#include "Tablero.h"
#include "Jugador.h" // Incluye el archivo de encabezado de Jugador


using namespace std;

class Juego {
public:
    Juego(const string& nombre1, const string& nombre2);

    void jugar();
    void mostrarResultados();

private:
    std::string nombreJugador1;
    std::string nombreJugador2;
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;

    void guardarResultado(const std::string& ganador, int contadorNegras, int contadorBlancas);
    // Otros miembros y funciones privadas de la clase Juego
};

#endif // JUEGO_H
