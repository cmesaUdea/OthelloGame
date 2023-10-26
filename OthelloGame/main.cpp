#include <iostream>
#include <windows.h>


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

    void mostrar() const{

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Utilizado para cambiar el color del texto en la consola

        cout << endl;
        cout << "   1   2   3   4   5   6   7   8" << endl;

        for (int i = 0; i < TAMANO; i++) {
            cout << "  +---+---+---+---+---+---+---+---+" << endl; //Parte superior del tablero
            cout << i + 1 << " "; // Imprime el número de cada fila
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == '*') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo para '*'
                } else if (celdas[i][j] == '-') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde para '-'
                } else if (movimientosPosibles[i][j]) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Azul para puntos de movimiento
                    cout << "| . ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    continue;
                }
                cout << "| " << celdas[i][j] << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            cout << "|" << endl;
        }
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }


    bool movimientoValido(int fila, int columna, char jugador) const {
        if (fila < 0 || fila >= TAMANO || columna < 0 || columna >= TAMANO || celdas[fila][columna] != ' ') {
            return false;
        }

        char rival = (jugador == '*') ? '-' : '*';

        bool valido = false;

        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (df == 0 && dc == 0) {
                    continue;
                }

                int f = fila + df;
                int c = columna + dc;

                if (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO && celdas[f][c] == rival) {
                    f += df;
                    c += dc;
                    while (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO) {
                        if (celdas[f][c] == ' ') {
                            break;
                        }
                        if (celdas[f][c] == jugador) {
                            valido = true;
                            break;
                        }
                        f += df;
                        c += dc;
                    }
                    if (valido) {
                        break;
                    }
                }
            }
            if (valido) {
                break;
            }
        }

        return valido;
    }

    void marcarMovimientosPosibles(char jugador) {
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                movimientosPosibles[i][j] = false;
            }
        }

        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == ' ') {
                    if (movimientoValido(i, j, jugador)) {
                        movimientosPosibles[i][j] = true;
                    }
                }
            }
        }
    }

    void realizarMovimiento(int fila, int columna, char jugador) {
        celdas[fila][columna] = jugador;
        char rival = (jugador == '*') ? '-' : '*';

        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (df == 0 && dc == 0) {
                    continue;
                }

                int f = fila + df;
                int c = columna + dc;
                bool fichasCapturadas = false;

                while (f >= 0 && f < TAMANO && c >= 0 && c < TAMANO) {
                    if (celdas[f][c] == rival) {
                        f += df;
                        c += dc;
                        fichasCapturadas = true;
                    } else if (celdas[f][c] == jugador) {
                        if (fichasCapturadas) {
                            f -= df;
                            c -= dc;
                            while (f != fila || c != columna) {
                                celdas[f][c] = jugador;
                                f -= df;
                                c -= dc;
                            }
                            break;
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    bool tableroCompleto() const {
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    int contarFichas(char jugador) const {
        int contador = 0;
        for (int i = 0; i < TAMANO; i++) {
            for (int j = 0; j < TAMANO; j++) {
                if (celdas[i][j] == jugador) {
                    contador++;
                }
            }
        }
        return contador;
    }


};


int main() {
    //Othello game; //Metodo para llamar al juego



    return 0;
}
