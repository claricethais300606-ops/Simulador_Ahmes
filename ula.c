#include "ula.h"

void atualizarNZ(Processador *cpu) {

    cpu->N = (cpu->AC >> 7) & 1;

    cpu->Z = (cpu->AC == 0);

}


// SOMA
void executarADD(Processador *cpu, unsigned char valor) {

    unsigned int resultado;

    resultado = cpu->AC + valor;

    cpu->C = (resultado > 255);

    cpu->V = ((~(cpu->AC ^ valor) & (cpu->AC ^ resultado)) >> 7) & 1;

    cpu->AC = resultado & 255;

    atualizarNZ(cpu);

}


// SUBTRACAO
void executarSUB(Processador *cpu, unsigned char valor) {

    int resultado;

    resultado = cpu->AC - valor;

    cpu->B = (cpu->AC < valor);

    cpu->V = (((cpu->AC ^ valor) & (cpu->AC ^ resultado)) >> 7) & 1;

    cpu->AC = resultado & 255;

    atualizarNZ(cpu);

}


// AND
void executarAND(Processador *cpu, unsigned char valor) {

    cpu->AC = cpu->AC & valor;

    atualizarNZ(cpu);

}


// OR
void executarOR(Processador *cpu, unsigned char valor) {

    cpu->AC = cpu->AC | valor;

    atualizarNZ(cpu);

}


// NOT
void executarNOT(Processador *cpu) {

    cpu->AC = ~cpu->AC;

    atualizarNZ(cpu);

}


// DESLOCAMENTO PARA DIREITA
void executarSHR(Processador *cpu) {

    cpu->C = cpu->AC & 1;

    cpu->AC = cpu->AC >> 1;

    atualizarNZ(cpu);

}


// DESLOCAMENTO PARA ESQUERDA
void executarSHL(Processador *cpu) {

    cpu->C = (cpu->AC >> 7) & 1;

    cpu->AC = cpu->AC << 1;

    atualizarNZ(cpu);

}


// ROTACAO PARA DIREITA
void executarROR(Processador *cpu) {

    unsigned char bit;

    bit = cpu->AC & 1;

    cpu->AC = (cpu->AC >> 1) | (bit << 7);

    cpu->C = bit;

    atualizarNZ(cpu);

}


// ROTACAO PARA ESQUERDA
void executarROL(Processador *cpu) {

    unsigned char bit;

    bit = (cpu->AC >> 7) & 1;

    cpu->AC = (cpu->AC << 1) | bit;

    cpu->C = bit;

    atualizarNZ(cpu);

}