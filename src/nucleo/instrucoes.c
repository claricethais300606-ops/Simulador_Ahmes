#include <stdio.h>
#include "instrucoes.h"
#include "memoria.h"
#include "ula.h"

int executarInstrucao(Processador *cpu, unsigned char codigo, unsigned char operando) {

    switch (codigo) {

        case NOP:
            break;

        case STA:
            escreverMemoria(operando, cpu->AC);
            break;

        case LDA:
            cpu->AC = lerMemoria(operando);
            atualizarNZ(cpu);
            break;

        case ADD:
            executarADD(cpu, lerMemoria(operando));
            break;

        case OR:
            executarOR(cpu, lerMemoria(operando));
            break;

        case AND:
            executarAND(cpu, lerMemoria(operando));
            break;

        case NOT:
            executarNOT(cpu);
            break;

        case SUB:
            executarSUB(cpu, lerMemoria(operando));
            break;

        case JMP:
            cpu->PC = operando;
            break;

        case JN:
            if (cpu->N == 1)
                cpu->PC = operando;
            break;

        case JP:
            if (cpu->N == 0)
                cpu->PC = operando;
            break;

        case JV:
            if (cpu->V == 1)
                cpu->PC = operando;
            break;

        case JNV:
            if (cpu->V == 0)
                cpu->PC = operando;
            break;

        case JZ:
            if (cpu->Z == 1)
                cpu->PC = operando;
            break;

        case JNZ:
            if (cpu->Z == 0)
                cpu->PC = operando;
            break;

        case JC:
            if (cpu->C == 1)
                cpu->PC = operando;
            break;

        case JNC:
            if (cpu->C == 0)
                cpu->PC = operando;
            break;

        case JB:
            if (cpu->B == 1)
                cpu->PC = operando;
            break;

        case JNB:
            if (cpu->B == 0)
                cpu->PC = operando;
            break;

        case SHR:
            executarSHR(cpu);
            break;

        case SHL:
            executarSHL(cpu);
            break;

        case ROR:
            executarROR(cpu);
            break;

        case ROL:
            executarROL(cpu);
            break;

        case HLT:
            cpu->parado = 1;
            break;

        default:
            printf("Erro: instrucao invalida! Codigo: 0x%02X\n", codigo);
            return 0;
    }

    return 1;
}