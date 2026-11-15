#include "processador.h"

void inicializarProcessador(Processador *cpu) {
    cpu->AC = 0;
    cpu->PC = 0;
    cpu->IR = 0;

    cpu->N = 0;
    cpu->Z = 0;
    cpu->C = 0;
    cpu->B = 0;
    cpu->V = 0;

    cpu->parado = 0;
}