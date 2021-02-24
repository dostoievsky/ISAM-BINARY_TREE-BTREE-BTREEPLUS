/* 
 * File:   Tp1.h
 */

#ifndef TP1_H
#define	TP1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>       
#include <chrono> 

#define M 2
#define MM 4

using namespace std;

typedef struct{
    int chave;
    double dado1;
    long int dado2;
    char dado3[501];
}TRegistro;

typedef struct{
    int comp;
    int transf;
}TAnalise;

int GeraArquivo(FILE *arq,int situacao,int n);
void AnaliseInicia(TAnalise *valores);
void Imprime (FILE *arq);

#endif	/* TP1_H */

