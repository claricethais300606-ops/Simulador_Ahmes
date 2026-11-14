#include <stdio.h>
#include "memoria.h"
#include "processador.h"
#include "instrucoes.h"
#include "ciclo.h"

int main() {

    Processador cpu;

    inicializarMemoria();
    inicializarProcessador(&cpu);

    escreverMemoria(100, 10);
    escreverMemoria(101, 5);

    // Teste LDA
    executarInstrucao(&cpu, LDA, 100);
    printf("LDA - AC: %d\n", cpu.AC);

    // Teste ADD
    executarInstrucao(&cpu, ADD, 101);
    printf("ADD - AC: %d\n", cpu.AC);

    // Teste STA
    executarInstrucao(&cpu, STA, 102);
    printf("STA - Memoria[102]: %d\n", lerMemoria(102));

    // Teste OR
    cpu.AC = 10;
    executarInstrucao(&cpu, OR, 101);
    printf("OR - AC: %d\n", cpu.AC);

    // Teste AND
    cpu.AC = 10;
    executarInstrucao(&cpu, AND, 101);
    printf("AND - AC: %d\n", cpu.AC);

    // Teste NOT
    cpu.AC = 15;
    executarInstrucao(&cpu, NOT, 0);
    printf("NOT - AC: %d\n", cpu.AC);

    // Teste SUB
    cpu.AC = 10;
    executarInstrucao(&cpu, SUB, 101);
    printf("SUB - AC: %d\n", cpu.AC);

    // Teste SHR
    cpu.AC = 129;
    executarInstrucao(&cpu, SHR, 0);
    printf("SHR - AC: %d | C: %d\n", cpu.AC, cpu.C);

    // Teste SHL
    cpu.AC = 129;
    executarInstrucao(&cpu, SHL, 0);
    printf("SHL - AC: %d | C: %d\n", cpu.AC, cpu.C);

    // Teste ROR
    cpu.AC = 129;
    cpu.C = 0;
    executarInstrucao(&cpu, ROR, 0);
    printf("ROR - AC: %d | C: %d\n", cpu.AC, cpu.C);

    // Teste ROL
    cpu.AC = 129;
    cpu.C = 0;
    executarInstrucao(&cpu, ROL, 0);
    printf("ROL - AC: %d | C: %d\n", cpu.AC, cpu.C);

    // Teste JMP
    executarInstrucao(&cpu, JMP, 50);
    printf("JMP - PC: %d\n", cpu.PC);

    // Teste HLT
    executarInstrucao(&cpu, HLT, 0);
    printf("HLT - Processador parado: %d\n", cpu.parado);

    // Testes dos saltos condicionais

    cpu.PC = 0;
    cpu.N = 1;
    executarInstrucao(&cpu, JN, 50);
    printf("JN - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.N = 0;
    executarInstrucao(&cpu, JP, 50);
    printf("JP - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.V = 1;
    executarInstrucao(&cpu, JV, 50);
    printf("JV - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.V = 0;
    executarInstrucao(&cpu, JNV, 50);
    printf("JNV - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.Z = 1;
    executarInstrucao(&cpu, JZ, 50);
    printf("JZ - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.Z = 0;
    executarInstrucao(&cpu, JNZ, 50);
    printf("JNZ - PC: %d\n", cpu.PC);
 
    cpu.PC = 0;
    cpu.C = 1;
    executarInstrucao(&cpu, JC, 50);
    printf("JC - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.C = 0;
    executarInstrucao(&cpu, JNC, 50);
    printf("JNC - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.B = 1;
    executarInstrucao(&cpu, JB, 50);
    printf("JB - PC: %d\n", cpu.PC);

    cpu.PC = 0;
    cpu.B = 0;
    executarInstrucao(&cpu, JNB, 50);
    printf("JNB - PC: %d\n", cpu.PC);

    // TESTE DO CICLO DO PROCESSADOR

    printf("\n--- TESTE DO CICLO ---\n");

    // Reinicia o processador
    inicializarProcessador(&cpu);

    // Dados
    escreverMemoria(100, 10);
    escreverMemoria(101, 5);

   // Programa na memória
    escreverMemoria(0, LDA);
    escreverMemoria(1, 100);

    escreverMemoria(2, ADD);
    escreverMemoria(3, 101);

    escreverMemoria(4, STA);
    escreverMemoria(5, 102);

    escreverMemoria(6, HLT);

   if (executarPrograma(&cpu) == 0) {
    printf("Erro durante a execucao!\n");
}

    printf("AC: %d\n", cpu.AC);
    printf("Memoria[102]: %d\n", lerMemoria(102));
    printf("PC: %d\n", cpu.PC);
    printf("Processador parado: %d\n", cpu.parado);

    // TESTE DE LOOP INFINITO

    printf("\n--- TESTE DE LIMITE DE EXECUCAO ---\n");

    inicializarProcessador(&cpu);

    escreverMemoria(0, JMP);
    escreverMemoria(1, 0);

    if (executarPrograma(&cpu) == 0) {
    printf("Loop interrompido corretamente!\n");
  }

    // TESTE DE INSTRUCAO INVALIDA

    printf("\n--- TESTE DE INSTRUCAO INVALIDA ---\n");

    inicializarProcessador(&cpu);

    escreverMemoria(0, 0xFF);

    if (executarPrograma(&cpu) == 0) {
    printf("Instrucao invalida identificada corretamente!\n");
  }

    return 0;

  } 