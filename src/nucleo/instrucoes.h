#ifndef INSTRUCOES_H
#define INSTRUCOES_H

#include "processador.h"

#define NOP  0x00
#define STA  0x10
#define LDA  0x20
#define ADD  0x30
#define OR   0x40
#define AND  0x50
#define NOT  0x60
#define SUB  0x70

#define JMP  0x80
#define JN   0x90
#define JP   0x94
#define JV   0x98
#define JNV  0x9C
#define JZ   0xA0
#define JNZ  0xA4
#define JC   0xB0
#define JNC  0xB4
#define JB   0xB8
#define JNB  0xBC

#define SHR  0xE0
#define SHL  0xE1
#define ROR  0xE2
#define ROL  0xE3

#define HLT  0xF0

int executarInstrucao(Processador *cpu, unsigned char codigo, unsigned char operando);

#endif