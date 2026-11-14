#ifndef MEMORIA_H
#define MEMORIA_H

#define TAMANHO_MEMORIA 256

void inicializarMemoria(void);
void escreverMemoria(int endereco, unsigned char valor);
unsigned char lerMemoria(int endereco);

#endif