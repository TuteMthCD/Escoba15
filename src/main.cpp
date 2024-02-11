#include <cstdio>
#include <cstdlib>

#include "cartas.h"

using namespace std;

void mezclar(carta_t _mazo[], int _len, int _depth) {
    for(int i = 0; i < _depth; i++) {
        srand(rand());
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

int main(int argc, char* argv[]) {

    mezclar(mazoCompleto, LEN_MAZO, 20000); // mezclo el maso completo

    // paso todo el maso a una pila, como una PILA DE CARTAS
    pila_t* pilaMesa = new pila_t();
    for(int i = 0; i < LEN_MAZO; i++) push(pilaMesa, mazoCompleto[i]);

    // creo la pila de cartas del jugador 1 y jugador 2
    pila_t* pilaJ1 = new pila_t();
    pila_t* pilaJ2 = new pila_t();

    // reparto 3 cartas a cada jugador, repartiendo una y una
    for(int i = i; i < 3; i++) {
        push(pilaJ1, pop(pilaMesa));
        push(pilaJ2, pop(pilaMesa));
    }

    // printeo para el debug
    printf("J1\n");
    while(pilaJ1->sgte != NULL) printf("carta %d \n", pop(pilaJ1).numero);
    printf("J2\n");
    while(pilaJ2->sgte != NULL) printf("carta %d \n", pop(pilaJ2).numero);


    return 0;
}
