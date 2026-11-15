#include <stdio.h>
#include "ciclo.h"
#include "memoria.h"
#include "instrucoes.h"

int executarCiclo(Processador *cpu) {

    unsigned char codigo;
    unsigned char operando = 0;

    if (cpu->parado == 1) {
        return 0;
    }

    codigo = lerMemoria(cpu->PC);

    cpu->IR = codigo;

    cpu->PC++;

    switch (codigo) {

        case NOP:
        case NOT:
        case SHR:
        case SHL:
        case ROR:
        case ROL:
        case HLT:
            break;

        case STA:
        case LDA:
        case ADD:
        case OR:
        case AND:
        case SUB:
        case JMP:
        case JN:
        case JP:
        case JV:
        case JNV:
        case JZ:
        case JNZ:
        case JC:
        case JNC:
        case JB:
        case JNB:

            operando = lerMemoria(cpu->PC);
            cpu->PC++;
            break;

        default:
    return executarInstrucao(cpu, codigo, operando);
    }


    return executarInstrucao(cpu, codigo, operando);
}

int executarPrograma(Processador *cpu) {

    int ciclos = 0;

    while (cpu->parado == 0) {

        if (ciclos >= 1000) {
            printf("Erro: limite de execucoes atingido!\n");
            return 0;
        }

        if (executarCiclo(cpu) == 0) {
            printf("Erro durante a execucao!\n");
            return 0;
        }

        ciclos++;
    }

    return 1;
}