

#ifndef PESQUISASEQUENCIAL_H
#define	PESQUISASEQUENCIAL_H

#define ITENSPAGINA 4

// TABELA DE INDICES

typedef struct{
    int posicao;
    int chave;
}TIndice;

void PesquisaSequencial(TRegistro *item, FILE *arq, int maxtabela);
int PesqSeqIndex(TIndice *tabela, int tam, TRegistro *item, FILE *arq,TAnalise *valores);


#endif	/* PESQUISASEQUENCIAL_H */

