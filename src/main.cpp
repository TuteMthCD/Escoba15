#include <cstddef>
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

bool recurMazo(list_t* _mazo, int _wanted, list_t*& _list) {

    if(_wanted < 0) return 0;

    if(_mazo->carta.valor == _wanted) {
        push(_list, _mazo->carta);
        return 1;
    } else {
        if(_mazo->sgte == NULL) return 0;
        int wanted = _wanted - _mazo->carta.valor;
        if(recurMazo(_mazo->sgte, wanted, _list)) {
            push(_list, _mazo->carta);
            return 1;
        }
        return 0;
    }
}

bool match(list_t* _jugador, list_t* _mesa, list_t*& _list) {
    list_t* mesa = _mesa;

    while(_jugador->sgte != NULL) {
        while(mesa->sgte != NULL) {
            if(recurMazo(mesa, 15 - _jugador->carta.valor, _list)) {
                push(_list, _jugador->carta);
                return 1;
            }
            mesa = mesa->sgte;
        }
        mesa = _mesa;
        _jugador = _jugador->sgte;
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

    // // reparto 3 cartas a cada jugador, repartiendo una y una
    // for(int i = 0; i < 3; i++) {
    //     if(Mazo->sgte != NULL) push(MazoJ1, pop(Mazo));
    //     if(Mazo->sgte != NULL) push(MazoJ2, pop(Mazo));
    // }
    //
    // for(int i = 0; i < 4; i++)
    //     if(Mazo->sgte != NULL) push(MazoMesa, pop(Mazo));

     push(MazoMesa, { 6, BASTO, 6 });
     push(MazoMesa, { 4, BASTO, 4 });
     push(MazoMesa, { 5, BASTO, 5 });
    
     push(MazoJ1, { 5, BASTO, 5 });

    list_t* Escoba = new list_t();
    match(MazoJ1, MazoMesa, Escoba);

    while(Escoba->sgte != NULL) {
        printf("%d,%d\n", Escoba->carta.valor, Escoba->carta.palo);
        Escoba = Escoba->sgte;
    }

    return 0;
}
