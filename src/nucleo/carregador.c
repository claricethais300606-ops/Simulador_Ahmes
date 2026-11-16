#include <stdio.h>
#include "carregador.h"
#include "memoria.h"

int carregarPrograma(const char *nomeArquivo) {

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo.\n");
        return 0;
    }

    unsigned char dados[TAMANHO_MEMORIA];
    unsigned int valor;
    int quantidade = 0;
    int resultado;

    while ((resultado = fscanf(arquivo, "%x", &valor)) == 1) {

        if (valor > 255) {
            printf("Erro: valor invalido no arquivo.\n");
            fclose(arquivo);
            return 0;
        }

        if (quantidade >= TAMANHO_MEMORIA) {
            printf("Erro: programa maior que a memoria.\n");
            fclose(arquivo);
            return 0;
        }

        dados[quantidade] = (unsigned char)valor;
        quantidade++;
    }

    if (resultado != EOF || quantidade == 0) {
        printf("Erro: arquivo vazio ou com formato invalido.\n");
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);

    inicializarMemoria();

    for (int i = 0; i < quantidade; i++) {
        escreverMemoria(i, dados[i]);
    }

    printf("Programa carregado com sucesso!\n");

    return 1;
}