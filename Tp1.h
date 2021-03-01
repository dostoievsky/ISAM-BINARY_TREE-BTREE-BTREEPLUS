#ifndef TP1_H
#define	TP1_H

//BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>       
#include <chrono> 

//CONSTANTES
#define M 2
#define MM 4

//EXCLUSÃO DE STD PARA FUNÇÕES
using namespace std;

//STRUCT QUE RECEBERA REGISTROS EM ARQUIVOS
typedef struct{
    int chave;
    double dado1;
    long int dado2;
    char dado3[501];
}TRegistro;

//STRUCT DE ANALISE DE DADOS DA EXECUÇÃO DO ALGORITMO
typedef struct{
    int comp;
    int transf;
}TAnalise;

//FUNÇÃO QUE GERA ARQUIVO BASEADO NO ARGUMENTO <QUANTIDADE>
int GeraArquivo(FILE *arq,int situacao,int n);
void AnaliseInicia(TAnalise *valores);
void Imprime (FILE *arq);

#endif	/* TP1_H */

