
#ifndef ARVOREB_H
#define	ARVOREB_H


#define TRUE 1
#define FALSE 0

//APONTADOR PARA PAGINA 
typedef struct TipoPagina * TipoApontador;

//ESTRUTURA DA PAGINA (O TREGISTRO ESTA DEFINIDO NO ARQUIVO TP1)
typedef struct TipoPagina {
    short n;
    TRegistro r[MM];   // VETOR DE REGISTROS DA PAGINA MM = 4
    TipoApontador p[MM + 1]; //VETOR DE APONTADORES PARA OS FILHOS MM + 1 =5
} TipoPagina;



void ArvoreB(FILE *arq, int chave);
void Inicializa(TipoApontador *Arvore);
int Pesquisa(TRegistro *x, TipoApontador Ap, TAnalise *valores);
void Ins(TRegistro Reg, TipoApontador Ap, short *Cresceu, TRegistro *RegRetorno, TipoApontador *ApRetorno, TAnalise *valores);
void InsereNaPagina(TipoApontador Ap, TRegistro Reg, TipoApontador ApDir, TAnalise *valores);
void Insere(TRegistro Reg, TipoApontador *Ap, TAnalise *valores);

#endif	/* ARVOREB_H */

