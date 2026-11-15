#ifndef CONTROLE_H
#define CONTROLE_H
#include "processador.h"
typedef struct {
    Processador cpu;
    unsigned long passos;
    unsigned char ultimo_endereco;
    unsigned char ultimo_codigo;
    unsigned char ultimo_operando;
    int tem_ultimo;
    int ultimo_resultado;
} Controle;
typedef struct {
    Processador antes;
    Processador depois;
    unsigned char endereco, codigo, operando;
    int tem_operando;
    int resultado;
} ResultadoPasso;
void inicializarControle(Controle *controle);
void reiniciarControle(Controle *controle);
int passoControle(Controle *controle, ResultadoPasso *resultado);
int executarContinuoControle(Controle *controle, unsigned int *quantidade);
const char *nomeInstrucao(unsigned char codigo);
int instrucaoTemOperando(unsigned char codigo);
#endif
