#include "interface.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static void binario(unsigned char v, char s[9]) {
    for(int i=7;i>=0;--i) s[7-i]=(v & (1u<<i)) ? '1':'0';
    s[8]='\0';
}
static void registrador(const char *nome,const char *descricao,unsigned char v) {
    char b[9]; binario(v,b);
    printf("%-3s | %-19s | %s | 0x%02X | %3u\n",nome,descricao,b,v,v);
}
static void flags(const Processador *c) {
    printf("N (Negativo): %u | Z (Zero): %u | C (Carry): %u | B (Borrow): %u | V (Overflow): %u\n",c->N,c->Z,c->C,c->B,c->V);
}
static void mostrarCPU(const Processador *c) {
    puts("\n============== ESTADO DO PROCESSADOR ==============");
    registrador("AC","Acumulador",c->AC);
    registrador("PC","Program Counter",c->PC);
    registrador("IR","Instruction Reg.",c->IR);
    puts("FLAGS:"); flags(c);
    printf("STATUS: %s\n",c->parado ? "PARADO" : "PRONTO PARA EXECUTAR");
}
static void mostrarPasso(const ResultadoPasso *r,int ok) {
    printf("\n========== EXECUCAO PASSO A PASSO ==========\n");
    printf("Endereco: 0x%02X | Instrucao: %s (0x%02X)\n",r->endereco,nomeInstrucao(r->codigo),r->codigo);
    if(r->tem_operando) printf("Operando: 0x%02X (%u)\n",r->operando,r->operando);
    printf("ANTES:  AC=%u PC=%u\n",r->antes.AC,r->antes.PC);
    printf("DEPOIS: AC=%u PC=%u\n",r->depois.AC,r->depois.PC);
    puts("FLAGS ANTES:"); flags(&r->antes);
    puts("FLAGS DEPOIS:"); flags(&r->depois);
    printf("Resultado: %s\n",ok ? (r->depois.parado ? "HLT - processador parado" : "Instrucao executada") : "Erro de instrucao");
    mostrarCPU(&r->depois);
}
static void estado(const Controle *c) {
    const Processador *p=&c->cpu;
    puts("\n============== ESTADO DA EXECUCAO ==============");
    printf("Situacao: %s\nPC: 0x%02X | AC: %u | IR: 0x%02X\n",p->parado ? "PARADO":"PRONTO PARA EXECUTAR",p->PC,p->AC,p->IR);
    if(!p->parado) {
        unsigned char op=lerMemoria(p->PC);
        printf("Proxima instrucao: %s (0x%02X)",nomeInstrucao(op),op);
        if(instrucaoTemOperando(op)) printf(" operando=0x%02X",lerMemoria((unsigned char)(p->PC+1)));
        putchar('\n');
    }
    if(c->tem_ultimo) printf("Ultima instrucao: %s em 0x%02X (%s)\n",nomeInstrucao(c->ultimo_codigo),c->ultimo_endereco,c->ultimo_resultado ? "OK":"ERRO");
    else puts("Ultima instrucao: nenhuma nesta sessao");
    printf("Passos executados nesta sessao: %lu\n",c->passos);
    flags(p);
}
static void ajuda(void) {
    puts("\n================ AJUDA AHMES ================");
    puts("Ahmes: simulador didatico de um processador de 8 bits.");
    puts("AC: acumulador; PC: endereco da proxima instrucao; IR: instrucao atual.");
    puts("N: resultado negativo; Z: resultado zero; C: carry; B: borrow; V: overflow.");
    puts("Passo a passo executa uma unica instrucao e mostra as alteracoes.");
    puts("Execucao completa segue ate HLT, erro ou limite de 1000 instrucoes.");
    puts("Reiniciar CPU zera registradores e flags, mas preserva a memoria.");
    puts("Use 0 para sair. O programa inicial e uma demonstracao embutida.");
    puts("Carregamento e visualizacao completa da memoria serao integrados depois.");
}
static int lerOpcao(int *opcao) {
    char linha[128], *fim;
    long numero;
    if(!fgets(linha,sizeof(linha),stdin)) return -1;
    size_t i=0;
    while(linha[i] && linha[i]!='\n') ++i;
    if(linha[i]!='\n' && !feof(stdin)) {
        int ch;
        while((ch=getchar())!='\n' && ch!=EOF) {}
        return 0;
    }
    errno=0;
    char *inicio=linha;
    while(isspace((unsigned char)*inicio)) ++inicio;
    if(!*inicio) return 0;
    numero=strtol(inicio,&fim,10);
    while(isspace((unsigned char)*fim)) ++fim;
    if(errno==ERANGE || *fim || numero<INT_MIN || numero>INT_MAX) return 0;
    *opcao=(int)numero;
    return 1;
}
void executarInterface(Controle *c) {
    for(;;) {
        int opcao;
        puts("\n=================================================");
        puts("                 SIMULADOR AHMES");
        puts("       ORGANIZACAO E ARQUITETURA DE COMPUTADORES");
        puts("=================================================");
        puts(" [1] Visualizar registradores e flags");
        puts(" [2] Executar proxima instrucao");
        puts(" [3] Executar programa completo");
        puts(" [4] Reiniciar processador");
        puts(" [5] Exibir estado da execucao");
        puts(" [6] Ajuda e instrucoes");
        puts(" [0] Sair");
        printf("Selecione uma opcao: "); fflush(stdout);
        int leitura=lerOpcao(&opcao);
        if(leitura<0) { puts("\nEntrada encerrada. Saindo."); return; }
        if(leitura==0) { puts("Entrada invalida. Digite um numero de 0 a 6."); continue; }
        switch(opcao) {
            case 0: puts("Encerrando simulador."); return;
            case 1: mostrarCPU(&c->cpu); break;
            case 2: {
                if(c->cpu.parado) { puts("CPU parada. Reinicie antes de executar."); break; }
                ResultadoPasso r;
                int ok=passoControle(c,&r);
                mostrarPasso(&r,ok>0);
                break;
            }
            case 3: {
                unsigned int quantidade=0;
                int motivo=executarContinuoControle(c,&quantidade);
                printf("\nInstrucoes executadas nesta operacao: %u\n",quantidade);
                if(motivo==1) puts("Fim: HLT encontrado.");
                else if(motivo==0) puts("Fim: instrucao invalida ou erro no nucleo.");
                else if(motivo==-1) puts("Fim: limite de seguranca de 1000 instrucoes atingido.");
                else puts("CPU ja estava parada. Reinicie antes de executar.");
                mostrarCPU(&c->cpu);
                break;
            }
            case 4: reiniciarControle(c); puts("CPU reiniciada. Memoria preservada."); break;
            case 5: estado(c); break;
            case 6: ajuda(); break;
            default: puts("Opcao inexistente. Escolha de 0 a 6."); break;
        }
    }
}
