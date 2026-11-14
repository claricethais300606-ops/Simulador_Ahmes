#include <stdio.h>
#include "ciclo.h"
#include "memoria.h"
#include "instrucoes.h"

int executarCiclo(Processador *cpu) {

    unsigned char codigo;
    unsigned char operando = 0;

    // Se o processador estiver parado, não executa nada
    if (cpu->parado == 1) {
        return 0;
    }

    // BUSCA: pega a instrução na memória
    codigo = lerMemoria(cpu->PC);

    // Guarda a instrução no registrador IR
    cpu->IR = codigo;

    // Avança o PC
    cpu->PC++;

    // DECODIFICAÇÃO: verifica se precisa de operando
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

            // Busca o operando na memória
            operando = lerMemoria(cpu->PC);
            cpu->PC++;
            break;

        default:
    return executarInstrucao(cpu, codigo, operando);
    }

    // EXECUÇÃO
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