#ifndef ARVOREBE_H
#define	ARVOREBE_H

#include "Tp1.h"

//ENUMERADOR DE PAGINA INTERNA E PAGINAS EXTERNAS
typedef enum {
  Interna, Externa
} TipoIntExt;

//NOMEANDO STRUCT APONTADOR DE PAGINA
typedef struct TipoPaginaEstrela *TipoApontadorEstrela;

//DECLARANDO
typedef struct TipoPaginaEstrela {
  //APONTADOR DE PAGINAS EXTERNAS OU INTERNA
  TipoIntExt Pt;
  //UNIÃO DE PAGINAS EXERTNAS DE INDICE COM 
  //A PAGINA INTERNA DE DADOS
  union {
    struct {
      int ni;
      //QUANTIDADE DE REGISTROS DE PAGINA INTERNA
      TRegistro ri[MM];
      //INDICE DE PAGINAS INTERNAS
      TipoApontadorEstrela pi[MM + 1];
    } U0;
    struct {
      int ne;
      //REGISTRO DE INDICES EXTERNOS
      TRegistro re[MM];
    } U1;
  } UU;
} TipoPaginaEstrela;

//
void ArvoreBE(FILE *arq, int chave);

//PESQUISA DADOS NA ARVORE
void Pesquisa(TRegistro *x, TipoApontadorEstrela *Ap);

//
void InsereNaPagina(TipoApontadorEstrela Ap, TRegistro Reg, TipoApontadorEstrela ApDir, TAnalise *valores);

//
void Insere(const TRegistro& Reg, TipoApontadorEstrela *Ap, TAnalise *valores);

//
void Ins(TRegistro Reg, TipoApontadorEstrela Ap, int *Cresceu, TRegistro *RegRetorno, TipoApontadorEstrela *ApRetorno, TAnalise *valores);


#endif	

