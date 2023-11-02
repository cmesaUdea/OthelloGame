#ifndef TABLERO_H
#define TABLERO_H

class Tablero {
public:
    static const int TAMANO = 8;
    char celdas[TAMANO][TAMANO];
    bool movimientosPosibles[TAMANO][TAMANO];

    Tablero();

    void mostrar() const;
    bool movimientoValido(int fila, int columna, char jugador) const;
    void marcarMovimientosPosibles(char jugador);
    void realizarMovimiento(int fila, int columna, char jugador);
    bool tableroCompleto() const;
    int contarFichas(char jugador) const;
};

#endif // TABLERO_H
