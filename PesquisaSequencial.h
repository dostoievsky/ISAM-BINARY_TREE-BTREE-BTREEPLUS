/* 
 * File:   PesquisaSequencial.h
 */

#ifndef PESQUISASEQUENCIAL_H
#define	PESQUISASEQUENCIAL_H

#include <stdio.h>
#include <stdlib.h>
#include "Tp1.h"

#define ITENSPAGINA 4

// Tabela de Indices - Arquivo Sequencial Indexado

typedef struct{
    int posicao;
    int chave;
}TIndice;

void PesquisaSequencial(TRegistro *item, FILE *arq, int maxtabela);
int PesqSeqIndex(TIndice *tabela, int tam, TRegistro *item, FILE *arq,TAnalise *valores);


#endif	/* PESQUISASEQUENCIAL_H */

