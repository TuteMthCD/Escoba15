#include <cstdio>
#include <cstdlib>

enum palo_e {
    BASTO,
    ESPADA,
    ORO,
    COPAS,
};

typedef struct {
    unsigned int numero;
    palo_e palo;
    int valor;
} carta_t;

//#define LEN_MAZO sizeof(mazo)/sizeof(carta_t) //manera correcta de hacerlo, yo voy a tomar la incorrecta
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
