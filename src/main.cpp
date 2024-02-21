#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "cartas.h"

using namespace std;

void mezclar(carta_t _mazo[], int _len, int _depth, unsigned int _seed) {
    for(int i = 0; i < _depth; i++) {
        srand(_seed + i);
        int rand0, rand1;

        do {
            rand0 = rand() % _len;
            rand1 = rand() % _len;
        } while(rand1 == rand0);

        carta_t aux = _mazo[rand0];
        _mazo[rand0] = _mazo[rand1];
        _mazo[rand1] = aux;
    }
}

int buscar15(list_t* _mesa, list_t* jugador) {
    list_t* mesa = _mesa;

    while(jugador->sgte != NULL) {
        while(mesa->sgte != NULL) {
            if(jugador->carta.valor + mesa->carta.valor == 15) {
                _mesa = mesa;
                return 1;
            } else
                mesa = mesa->sgte;
        }
        mesa = _mesa;
        jugador = jugador->sgte;
    }
    return 0;
}

int main(int argc, char* argv[]) {

    unsigned int seed = (unsigned int)time(nullptr);
    printf("seed:%d\n", seed);

    mezclar(mazoCompleto, LEN_MAZO, 20000, seed); // mezclo el maso completo

    // paso todo el maso a una pila, como una PILA DE CARTAS
    list_t* Mazo = new list_t();
    for(int i = 0; i < LEN_MAZO; i++) push(Mazo, mazoCompleto[i]);

    // creo la pila de cartas del jugador 1 y jugador 2
    list_t* MazoJ1 = new list_t();
    list_t* MazoJ2 = new list_t();

    // creo la pila de la mesa
    list_t* MazoMesa = new list_t();

    // reparto 3 cartas a cada jugador, repartiendo una y una
    for(int i = 0; i < 3; i++) {
        if(Mazo->sgte != NULL) push(MazoJ1, pop(Mazo));
        if(Mazo->sgte != NULL) push(MazoJ2, pop(Mazo));
    }

    for(int i = 0; i < 4; i++)
        if(Mazo->sgte != NULL) push(MazoMesa, pop(Mazo));
    return 0;
}
