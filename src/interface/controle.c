#include "controle.h"
#include "ciclo.h"
#include "memoria.h"
#include "instrucoes.h"
#include <string.h>

typedef struct { unsigned char codigo; const char *nome; int operando; } DefInstrucao;
static const DefInstrucao defs[] = {
    {NOP,"NOP",0},{STA,"STA",1},{LDA,"LDA",1},{ADD,"ADD",1},
    {OR,"OR",1},{AND,"AND",1},{NOT,"NOT",0},{SUB,"SUB",1},
    {JMP,"JMP",1},{JN,"JN",1},{JP,"JP",1},{JV,"JV",1},
    {JNV,"JNV",1},{JZ,"JZ",1},{JNZ,"JNZ",1},{JC,"JC",1},
    {JNC,"JNC",1},{JB,"JB",1},{JNB,"JNB",1},
    {SHR,"SHR",0},{SHL,"SHL",0},{ROR,"ROR",0},{ROL,"ROL",0},{HLT,"HLT",0}
};
static const DefInstrucao *buscar(unsigned char codigo) {
    for (unsigned int i=0; i<sizeof(defs)/sizeof(defs[0]); ++i)
        if (defs[i].codigo==codigo) return &defs[i];
    return NULL;
}
const char *nomeInstrucao(unsigned char codigo) {
    const DefInstrucao *d=buscar(codigo); return d ? d->nome : "INVALIDA";
}
int instrucaoTemOperando(unsigned char codigo) {
    const DefInstrucao *d=buscar(codigo); return d ? d->operando : 0;
}
void inicializarControle(Controle *c) {
    memset(c,0,sizeof(*c)); inicializarProcessador(&c->cpu);
}
void reiniciarControle(Controle *c) {
    inicializarProcessador(&c->cpu);
    c->passos=0; c->tem_ultimo=0; c->ultimo_resultado=0;
}
int passoControle(Controle *c, ResultadoPasso *r) {
    memset(r,0,sizeof(*r));
    r->antes=c->cpu;
    if(c->cpu.parado) { r->depois=c->cpu; return -1; }
    r->endereco=c->cpu.PC;
    r->codigo=lerMemoria(r->endereco);
    r->tem_operando=instrucaoTemOperando(r->codigo);
    if(r->tem_operando) r->operando=lerMemoria((unsigned char)(r->endereco+1));
    r->resultado=executarCiclo(&c->cpu);
    r->depois=c->cpu;
    c->passos++;
    c->ultimo_endereco=r->endereco;
    c->ultimo_codigo=r->codigo;
    c->ultimo_operando=r->operando;
    c->tem_ultimo=1;
    c->ultimo_resultado=r->resultado;
    return r->resultado ? 1 : 0;
}
int executarContinuoControle(Controle *c, unsigned int *quantidade) {
    *quantidade=0;
    if(c->cpu.parado) return 2;
    while(!c->cpu.parado && *quantidade<1000) {
        ResultadoPasso r;
        int ok=passoControle(c,&r);
        ++*quantidade;
        if(ok==0) return 0;
        if(ok<0) return 2;
    }
    return c->cpu.parado ? 1 : -1;
}
