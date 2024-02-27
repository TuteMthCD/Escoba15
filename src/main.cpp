#include <ctime> // para obtener aleatorios.
#include <iostream>

enum palo_e {
    BASTO,
    ESPADA,
    ORO,
    COPAS,
};

struct carta_t {
    unsigned int numero;
    palo_e palo;
    int valor;

    // para poder comparar 2 cartas.
    bool operator==(const carta_t& carta) const {
        return numero == carta.numero && palo == carta.palo && valor == carta.valor;
    }
};

// #define LEN_MAZO sizeof(mazo)/sizeof(carta_t) //manera correcta de hacerlo, yo voy a tomar la incorrecta
#define LEN_MAZO 40

carta_t mazoCompleto[] = {
    { 1, BASTO, 1 },
    { 2, BASTO, 2 },
    { 3, BASTO, 3 },
    { 4, BASTO, 4 },
    { 5, BASTO, 5 },
    { 6, BASTO, 6 },
    { 7, BASTO, 7 },
    { 10, BASTO, 8 },
    { 11, BASTO, 9 },
    { 12, BASTO, 10 },

    { 1, ESPADA, 1 },
    { 2, ESPADA, 2 },
    { 3, ESPADA, 3 },
    { 4, ESPADA, 4 },
    { 5, ESPADA, 5 },
    { 6, ESPADA, 6 },
    { 7, ESPADA, 7 },
    { 10, ESPADA, 8 },
    { 11, ESPADA, 9 },
    { 12, ESPADA, 10 },

    { 1, ORO, 1 },
    { 2, ORO, 2 },
    { 3, ORO, 3 },
    { 4, ORO, 4 },
    { 5, ORO, 5 },
    { 6, ORO, 6 },
    { 7, ORO, 7 },
    { 10, ORO, 8 },
    { 11, ORO, 9 },
    { 12, ORO, 10 },

    { 1, COPAS, 1 },
    { 2, COPAS, 2 },
    { 3, COPAS, 3 },
    { 4, COPAS, 4 },
    { 5, COPAS, 5 },
    { 6, COPAS, 6 },
    { 7, COPAS, 7 },
    { 10, COPAS, 8 },
    { 11, COPAS, 9 },
    { 12, COPAS, 10 },
};

struct list_t {
    carta_t carta;
    list_t* sgte = NULL;
};

void push(list_t*& _lista, carta_t _carta) {
    list_t* pointer = new list_t(); // creo nuevo puntero
    pointer->carta = _carta;        // agrego la carta
    pointer->sgte = _lista;
    _lista = pointer;
}

carta_t pop(list_t*& _lista) {
    carta_t carta = { 0, BASTO, 0 };
    list_t* pointer = _lista;
    carta = pointer->carta;
    _lista = pointer->sgte;
    delete pointer;
    return carta;
}
bool remove(list_t*& _lista, carta_t _carta) {
    list_t* pointer = _lista;

    if(pointer->carta == _carta) {
        _lista = pointer->sgte;
        delete pointer;
    }

    while(pointer->sgte != NULL) {
        if(pointer->sgte->carta == _carta) {
            list_t* dpointer = pointer->sgte;
            pointer->sgte = dpointer->sgte;
            delete dpointer;
        } else
            pointer = pointer->sgte;
    }

    return false;
}

void clean(list_t*& _lista) {
    while(_lista->sgte != NULL) { pop(_lista); }
}

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

bool junte15(list_t*& _mesa, list_t*& _jugador, list_t*& _casita) {
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

void printCartas(list_t* _lista,const char* _name) {
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

void conteo(list_t* J1, list_t* J2, int& PuntosJ1, int& PuntosJ2) {
    int Cartas_J1 = 0, ORO_J1 = 0, C7_J1 = 0;
    int Cartas_J2 = 0, ORO_J2 = 0, C7_J2 = 0;

    while(J1->sgte != NULL) {
        Cartas_J1++;

        if(J1->carta.palo == ORO) ORO_J1++;

        if(J1->carta.numero == 7) C7_J1++;

        if(J1->carta.numero == 7 && J1->carta.palo == ORO) PuntosJ1++;

        J1 = J1->sgte;
    }
    while(J2->sgte != NULL) {
        Cartas_J2++;

        if(J2->carta.palo == ORO) ORO_J2++;

        if(J2->carta.numero == 7) C7_J2++;

        if(J2->carta.numero == 7 && J2->carta.palo == ORO) PuntosJ2++;

        J2 = J2->sgte;
    }

    if(Cartas_J1 != Cartas_J2) {
        if(Cartas_J1 > Cartas_J2)
            PuntosJ1++;
        else
            PuntosJ2++;
    }

    if(C7_J1 != C7_J2) {
        if(C7_J1 > C7_J2)
            PuntosJ1++;
        else
            PuntosJ2++;
    }

    if(ORO_J1 != ORO_J2) {
        if(ORO_J1 > ORO_J2)
            PuntosJ1++;
        else
            PuntosJ2++;
    }
}

int main(int argc, char* argv[]) {

    using namespace std;

    int PuntosJ1 = 0, PuntosJ2 = 0;
    // creo la pila de la mesa
    list_t* MazoMesa = new list_t();

    // creo la pila de cartas del jugador 1 y jugador 2
    // y tambien sus casitas(?)
    list_t* ManoJ1 = new list_t();
    list_t* JunteJ1 = new list_t();
    list_t* ManoJ2 = new list_t();
    list_t* JunteJ2 = new list_t();
    list_t* Mazo = new list_t();

    int seed = time(nullptr);

    do {
        cout << "Semilla: " << seed << endl;

        cout << "Se mezcla el mazo 20000 veces" << endl;
        mezclar(mazoCompleto, LEN_MAZO, 20000, seed); // mezclo el maso completo

        // paso todo el maso a una lista, como una PILA DE CARTAS
        for(int i = 0; i < LEN_MAZO; i++) push(Mazo, mazoCompleto[i]);

        bool ultimo = 0; // variable para saber quien es el ultimo en juntar

        // Empieza la partida
        // reparto 3 cartas a cada jugador, repartiendo una y una

        cout << "Pulsa para Repartir" << endl;
        // getchar();

        for(int i = 0; i < 3; i++) {
            if(Mazo->sgte != NULL) push(ManoJ1, pop(Mazo));
            if(Mazo->sgte != NULL) push(ManoJ2, pop(Mazo));
        }
        // suelto 4 cartas a la mesa;
        for(int i = 0; i < 4; i++)
            if(Mazo->sgte != NULL) push(MazoMesa, pop(Mazo));


        do { // el juego termina cuando el mazo no tiene mas cartas.

            printCartas(ManoJ1, "ManoJ1");
            printCartas(ManoJ2, "ManoJ2");
            printCartas(MazoMesa, "Mesa");
            // getchar();
            if(junte15(MazoMesa, ManoJ1, JunteJ1)) {

                if(MazoMesa->sgte == NULL) {
                    PuntosJ1++;
                    cout << "-ESCOBA J1" << endl;
                }

                ultimo = 0;

            } else {
                if(ManoJ1->sgte != NULL) push(MazoMesa, pop(ManoJ1));
            }
            if(junte15(MazoMesa, ManoJ2, JunteJ2)) {

                if(MazoMesa->sgte == NULL) {
                    PuntosJ2++;
                    cout << "-ESCOBA J2" << endl;
                }

                ultimo = 1;

            } else {
                if(ManoJ2->sgte != NULL) push(MazoMesa, pop(ManoJ2));
            }


            // cuando los 2 se quedan sin cartas reparte 3 a cada uno, una y una.
            if(ManoJ1->sgte == NULL && ManoJ2->sgte == NULL) {
                for(int i = 0; i < 3; i++) {
                    if(Mazo->sgte != NULL) push(ManoJ1, pop(Mazo));
                    if(Mazo->sgte != NULL) push(ManoJ2, pop(Mazo));
                }
            }


        } while(Mazo->sgte != NULL || ManoJ1->sgte != NULL || ManoJ2->sgte != NULL);

        printCartas(MazoMesa, "SOBRA");
        // le da las cartas al ultimo jugador en levantar
        //
        if(ultimo == 0) {
            while(MazoMesa->sgte != NULL) push(JunteJ1, pop(MazoMesa));
        } else
            while(MazoMesa->sgte != NULL) push(JunteJ2, pop(MazoMesa));

        conteo(JunteJ1, JunteJ2, PuntosJ1, PuntosJ2);

        // printCartas(JunteJ1, "JunteJ1");
        // printCartas(JunteJ2, "JunteJ2");

        cout << "PuntosJ1:" << PuntosJ1 << " PuntosJ2:" << PuntosJ2 << endl;

        seed++;

        clean(MazoMesa);
        clean(ManoJ1);
        clean(ManoJ2);
        clean(JunteJ1);
        clean(JunteJ2);

        cout << "--------------- TERMINO LA RONDA -------------------------" << endl;
        // getchar();
    } while(PuntosJ1 < 15 && PuntosJ2 < 15 || PuntosJ1 == PuntosJ2);

    // 17 < 15 = 0;
    // 17 < 15 = 0;
    // 17 == 17 = 1;
    //
    // 0.0+1 = 1;

    if(PuntosJ1 > PuntosJ2) {
        cout << "Gano Jugador 1 con: " << PuntosJ1 << " Puntos";
    } else {
        cout << "Gano Jugador 2 con: " << PuntosJ2 << " Puntos";
    }
    return 0;
}
