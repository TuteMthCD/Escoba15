#include <cstddef>
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

void push(list_t*& _pila, carta_t _carta) {
    list_t* pointer = new list_t(); // creo nuevo puntero
    pointer->carta = _carta;        // agrego la carta
    pointer->sgte = _pila;
    _pila = pointer;
}

carta_t pop(list_t*& _pila) {
    carta_t carta = {0,BASTO,0}; 
    list_t* pointer = _pila;
    carta = pointer->carta;
    _pila = pointer->sgte;
    delete pointer;
    return carta;
}
bool remove(list_t*& _pila, carta_t _carta) {
    list_t* pointer = _pila;
    while(pointer->sgte->sgte != NULL) {
        if(_carta == pointer->sgte->carta) {
            list_t* dPointer = pointer->sgte;
            pointer->sgte = dPointer->sgte;
            delete dPointer;
            return true;
        }
        pointer = pointer->sgte;
    }
    return false;
}
