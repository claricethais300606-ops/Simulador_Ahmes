#include <stdio.h>
#include "memoria.h"

unsigned char memoria[TAMANHO_MEMORIA];

void inicializarMemoria(void) {

    for (int i = 0; i < TAMANHO_MEMORIA; i++) {
        memoria[i] = 0;
    }

}

void escreverMemoria(int endereco, unsigned char valor) {

    if (endereco >= 0 && endereco < TAMANHO_MEMORIA) {
        memoria[endereco] = valor;
    }
    else {
        printf("Erro: endereco invalido!\n");
    }

}

unsigned char lerMemoria(int endereco) {

    if (endereco >= 0 && endereco < TAMANHO_MEMORIA) {
        return memoria[endereco];
    }

    printf("Erro: endereco invalido!\n");

    return 0;
}