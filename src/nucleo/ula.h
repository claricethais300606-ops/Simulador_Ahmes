#ifndef ULA_H
#define ULA_H

#include "processador.h"

void atualizarNZ(Processador *cpu);

void executarADD(Processador *cpu, unsigned char valor);

void executarSUB(Processador *cpu, unsigned char valor);

void executarAND(Processador *cpu, unsigned char valor);

void executarOR(Processador *cpu, unsigned char valor);

void executarNOT(Processador *cpu);

void executarSHR(Processador *cpu);

void executarSHL(Processador *cpu);

void executarROR(Processador *cpu);

void executarROL(Processador *cpu);

#endif