#include <iostream>


using namespace std;

class Tablero {


public:
    //Para el tamaño del tablero, el cual sera una matriz de tipo char
    static const int TAMANO = 8;
    char celdas[TAMANO][TAMANO];

    Tablero(){ //Metodo constructor de un tablero en la memoria
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                celdas[i][j] = ' ';
            }
        }

        //Celdas en la que se tienen las fichas iniciales
        celdas[3][3] = celdas[4][4] = '-';
        celdas[3][4] = celdas[4][3] = '*';
    }



};



int main() {
    //Othello game; //Metodo para llamar al juego



    return 0;
}
