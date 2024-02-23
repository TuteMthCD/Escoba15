#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>

#include "cartas.h"

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

    // condiciones importantes
    if(_wanted <= 0) return 0;
    if(_mazo->sgte == NULL) return 0;

    // si el valor de la carta que sigue es el que busco retorno 1
    // y meto la carta a la pila
    if(_mazo->carta.valor == _wanted) {
        push(_list, _mazo->carta);
        return 1;
    } else {                                        // si no es el valor
        int wanted = _wanted - _mazo->carta.valor;  // calculo el valor que sigue, y necesito
        if(recurMazo(_mazo->sgte, wanted, _list)) { // le paso el siguente del mazo
            push(_list, _mazo->carta);
            return 1;
        }
    }

    if(recurMazo(_mazo->sgte, _wanted, _list)) { // le paso el siguente del mazo y vuelvo a llamar
        return 1;
    }
    return 0; // significa que no hay ninguna combinacion posible
}

bool escoba(list_t*& _mesa, list_t*& _jugador, list_t*& _casita) {
    list_t* jugador = _jugador;
    list_t* mesa = _mesa;

    if(mesa->sgte == NULL) return 0;
    if(jugador->sgte == NULL) return 0;

    while(jugador->sgte != NULL) {
        if(recurMazo(mesa, 15 - jugador->carta.valor, _casita)) {
            push(_casita, jugador->carta); // meto el mazo del jugador a la _casita

            remove(_jugador, jugador->carta); // remuevo del jugador la carta;

            // remevo de la mesa todas las cartas con las que el jugador hizo escoba
            list_t* casita = _casita;
            while(casita->sgte != NULL) {
                remove(_mesa, casita->carta);
                casita = casita->sgte;
            }
            return 1;
        }
        jugador = jugador->sgte;
    }

    return 0;
}

void printCartas(list_t* _lista, std::string _name) {
    using namespace std;

    cout << "-------------" << _name << "------------" << endl;

    while(_lista->sgte != NULL) {
        cout << _lista->carta.numero;

        switch(_lista->carta.palo) {
        case BASTO: cout << " BASTO "; break;
        case ESPADA: cout << " ESPADA "; break;
        case ORO: cout << " ORO "; break;
        case COPAS: cout << " COPAS "; break;
        default: cout << "carta sin palo????"; break;
        }

        cout << _lista->carta.valor << endl;

        _lista = _lista->sgte;
    }
}

int main(int argc, char* argv[]) {

    using namespace std;

    unsigned int seed = (unsigned int)time(nullptr);
    cout << "Semilla: " << seed << endl;


    mezclar(mazoCompleto, LEN_MAZO, 20000, seed); // mezclo el maso completo

    // paso todo el maso a una lista, como una PILA DE CARTAS
    list_t* Mazo = new list_t();
    for(int i = 0; i < LEN_MAZO; i++) push(Mazo, mazoCompleto[i]);

    // creo la pila de la mesa
    list_t* MazoMesa = new list_t();

    // creo la pila de cartas del jugador 1 y jugador 2
    // y tambien sus casitas(?)
    list_t* MazoJ1 = new list_t();
    list_t* EscobaJ1 = new list_t();
    list_t* MazoJ2 = new list_t();
    list_t* EscobaJ2 = new list_t();


    // Empieza la partida

    while(Mazo->sgte != NULL) { // el juego termina cuando el mazo no tiene mas cartas.

        // reparto 3 cartas a cada jugador, repartiendo una y una
        for(int i = 0; i < 3; i++) {
            if(Mazo->sgte != NULL) push(MazoJ1, pop(Mazo));
            if(Mazo->sgte != NULL) push(MazoJ2, pop(Mazo));
        }

        // suelto 4 cartas a la mesa;
        for(int i = 0; i < 4; i++)
            if(Mazo->sgte != NULL) push(MazoMesa, pop(Mazo));


        escoba(MazoMesa, MazoJ1, EscobaJ1); // busco escoba en MazoJ1 y lo guardo en EscobaJ1
        escoba(MazoMesa, MazoJ2, EscobaJ2); // busco escoba en MazoJ2 y lo guardo es EscobaJ2
    }


    printCartas(Mazo, "Mazo");
    printCartas(MazoMesa, "Mesa");

    printCartas(MazoJ1, "MazoJ1");
    printCartas(EscobaJ1, "EscobaJ1");
    printCartas(MazoJ1, "MazoJ1");
    printCartas(EscobaJ2, "EscobaJ2");

    return 0;
}
