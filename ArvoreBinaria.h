/* 
 * File:   ArvoreBinaria.h
 */

#ifndef ARVOREBINARIA_H
#define	ARVOREBINARIA_H

typedef struct {
    int chave;
    int pEsq;
    int pDir;
} TNo;

void ArvoreBinaria(FILE *arq, TRegistro chave);
void GeraTabela(FILE *arq, FILE *tabela, TAnalise *valores);
void VerificaTabela(FILE *tabela, int *indice, int chave, int index, TAnalise *valores);
int PesquisaArvoreBin(FILE *tabela, int chave, int index, FILE* arq, TRegistro *item, TAnalise *valores);



#endif	/* ARVOREBINARIA_H */

