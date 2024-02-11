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

    carta_t mazoMezcla[LEN_MAZO];
    for(int i = 0; i < LEN_MAZO; i++) mazoMezcla[i] = mazoCompleto[i];

    mezclar(mazoMezcla, LEN_MAZO, 20000);

    printf("----------------------------------------------------------");

    for(int i = 0; i < LEN_MAZO; i++) {
        carta_t carta = mazoMezcla[i];
        switch(carta.palo) {
        case BASTO: printf("%d de BASTO \n", carta.numero); break;
        case ESPADA: printf("%d de ESPADA \n", carta.numero); break;
        case ORO: printf("%d de ORO \n", carta.numero); break;
        case COPAS: printf("%d de COPAS \n", carta.numero); break;
        }
    }

    return 0;
}
