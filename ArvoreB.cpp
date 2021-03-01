#include "Tp1.h"
#include "ArvoreB.h"


void Inicializa (TipoApontador *Arvore)
{
    *Arvore = NULL;
}
 
void ArvoreB(FILE *arq, int chave)
{
    TipoApontador Ap;
    TRegistro item;
    
    TAnalise valores;
    AnaliseInicia(&valores);
    
    Ap=(TipoApontador)malloc(sizeof(TipoPagina));
    Inicializa (&Ap);
    while (fread(&item, sizeof(TRegistro), 1, arq) == 1)
    {
        valores.transf++;
        Insere(item, &Ap, &valores);
    }
    item.chave=chave;
    
    printf("Comparacoes geracao: %d\n", valores.comp);
    
    Pesquisa(&item ,Ap, &valores);
    
    printf("\n Medidas\n");
    printf("Comparações: %d.\nTransferencias: %d.\n\n", valores.comp, valores.transf);

}

int Pesquisa(TRegistro *x, TipoApontador Ap, TAnalise *valores)
{
    long i = 1;
    
    if (Ap == NULL)
    { 
        //valores->comp++;
        printf("Registro nao esta presente na arvore\n");
        return 0;
    }
    while (i < Ap->n && x->chave > Ap->r[i-1].chave)
    { 
        valores->comp++;
        i++;
    }

    if (x->chave == Ap->r[i-1].chave)
    { 
        valores->comp++;
        *x = Ap->r[i-1];
        printf("Chave encontrada!\n");
        printf("Chave: %d.\n", x->chave);
        printf("Dado1: %.2lf\n", x->dado1);
        printf("Dado2: %ld\n", x->dado2);
        printf("Dado3: %s.\n", x->dado3);
        printf("\n Medidas\n");
        return 1;
    }
    if (x->chave < Ap->r[i-1].chave)
    {
        valores->comp++;
        Pesquisa(x, Ap->p[i-1], valores);
    }
    else
    {
        valores->comp++;
        Pesquisa(x, Ap->p[i], valores);
    }
    return 0;
}

void InsereNaPagina(TipoApontador Ap, TRegistro Reg, TipoApontador ApDir, TAnalise *valores)
{
    int k;
    int NaoAchouPosicao;

    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->r[k - 1].chave)
        {
            valores->comp++;
            NaoAchouPosicao = 0;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(TRegistro Reg, TipoApontador Ap, int *Cresceu, TRegistro *RegRetorno, TipoApontador *ApRetorno, TAnalise *valores)
{
    TipoApontador ApTemp;
    long i=1, j;
    
    if (Ap == NULL)
    {
        valores->comp++;
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave)
        i++;

    if (Reg.chave == Ap->r[i - 1].chave)
    {   
        valores->comp++;
        //printf("O registro ja esta presente.\n");
        *Cresceu = 0;
        return;
    }

    if (Reg.chave < Ap->r[i - 1].chave)
    {
        valores->comp++;
        i--;
    }
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, valores);
    if (!*Cresceu)
        return;
    if (Ap->n < MM)
    {
        valores->comp++;
        //Pagina tem espaco 
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, valores);
        *Cresceu = 0;
        return;
    }
    // Overflow: Pagina tem que ser dividida 
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i <= M + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM], valores);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, valores);
    }
    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, valores);
    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j], valores);
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
} 

void Insere(TRegistro Reg, TipoApontador *Ap, TAnalise *valores)
{
    int Cresceu;
    TRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, valores);

    if (Cresceu)   // Arvore cresce na altura pela raiz 
    {
        valores->comp++;
        ApTemp=(TipoPagina*)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = (*Ap);
        *Ap = ApTemp;
    }
}