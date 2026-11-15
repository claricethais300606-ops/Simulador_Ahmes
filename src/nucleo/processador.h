#ifndef PROCESSADOR_H
#define PROCESSADOR_H

typedef struct {
    unsigned char AC;
    unsigned char PC;
    unsigned char IR;

    unsigned char N;
    unsigned char Z;
    unsigned char C;
    unsigned char B;
    unsigned char V;

    unsigned char parado;
} Processador;

void inicializarProcessador(Processador *cpu);

#endif