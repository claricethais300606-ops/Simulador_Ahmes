#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "controle.h"
#include "memoria.h"
#include "instrucoes.h"

int executarTestesOriginais(void);
int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--testes") == 0) return executarTestesOriginais();
    if (argc != 1) { fprintf(stderr, "Uso: %s [--testes]\n", argv[0]); return 1; }
    inicializarMemoria();
    /* Programa de demonstracao ate a integracao do carregador de arquivos. */
    escreverMemoria(100, 10); escreverMemoria(101, 5);
    escreverMemoria(0, LDA); escreverMemoria(1, 100);
    escreverMemoria(2, ADD); escreverMemoria(3, 101);
    escreverMemoria(4, STA); escreverMemoria(5, 102);
    escreverMemoria(6, HLT);
    Controle controle;
    inicializarControle(&controle);
    executarInterface(&controle);
    return 0;
}
