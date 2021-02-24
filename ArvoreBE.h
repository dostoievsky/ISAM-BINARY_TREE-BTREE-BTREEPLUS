/* 
 * File:   ArvoreBE.h
 */

#ifndef ARVOREBE_H
#define	ARVOREBE_H

#include <stdio.h>
#include <stdlib.h>
//#define M  1
//#define MM 2

//typedef long TipoChave;
typedef enum {
  Interna, Externa
} TipoIntExt;
typedef struct TipoPaginaEstrela *TipoApontadorEstrela;
typedef struct TipoPaginaEstrela {
  TipoIntExt Pt;
  union {
    struct {
      int ni;
      TRegistro ri[MM];
      TipoApontadorEstrela pi[MM + 1];
    } U0;
    struct {
      int ne;
      TRegistro re[MM];
    } U1;
  } UU;
} TipoPaginaEstrela;

void ArvoreBE(FILE *arq, int chave);
void Pesquisa(TRegistro *x, TipoApontadorEstrela *Ap);
void InsereNaPagina(TipoApontadorEstrela Ap, TRegistro Reg, TipoApontadorEstrela ApDir, TAnalise *valores);
void Insere(TRegistro Reg, TipoApontadorEstrela *Ap, TAnalise *valores);
void Ins(TRegistro Reg, TipoApontadorEstrela Ap, int *Cresceu, TRegistro *RegRetorno, TipoApontadorEstrela *ApRetorno, TAnalise *valores);


#endif	/* ARVOREBE_H */

