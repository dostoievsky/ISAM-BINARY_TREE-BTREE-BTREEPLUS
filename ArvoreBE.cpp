#include "Tp1.h"
#include "ArvoreBE.h"

void Inicializa (TipoApontadorEstrela *Arvore)
{
    *Arvore = NULL;
}

void Pesquisa(TRegistro *x, TipoApontadorEstrela *Ap) {
    int i;
    TipoApontadorEstrela Pag;
    Pag = *Ap;
    if ((*Ap)->Pt == Interna) {
        i = 1;
        while (i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i - 1].chave)  
			i++;
        if (x->chave < Pag->UU.U0.ri[i - 1].chave) 
			Pesquisa(x, &Pag->UU.U0.pi[i - 1]);
        else 
			Pesquisa(x, &Pag->UU.U0.pi[i]);
        return;
    }
    i = 1;
    while (i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i - 1].chave) //pesquisa na pagina folha 
		i++;
    if (x->chave == Pag->UU.U1.re[i - 1].chave)
    {
	//valores->comp++;
        *x = Pag->UU.U1.re[i - 1];
        
        printf("Chave encontrada!\n");
        printf("Chave: %d.\n", x->chave);
        printf("Dado1: %.2lf\n", x->dado1);
        printf("Dado2: %ld\n", x->dado2);
        printf("Dado3: %s.\n", x->dado3);
        printf("\n Medidas\n");
        return;
    }
    else 
		printf("TipoRegistro nao esta presente na arvore\n");
}

void InsereNaPagina(TipoApontadorEstrela Ap, TRegistro Reg, TipoApontadorEstrela ApDir, TAnalise *valores)
{//insere registro na pagina (folha ou indice)
    int k;
    int NaoAchouPosicao;

    if(Ap->Pt == Interna){ //se for nó interno(indice) busca na arvore onde o registro será inserido
		k = Ap->UU.U0.ni;
		NaoAchouPosicao = (k > 0);
		while(NaoAchouPosicao) 
		{
			if (Reg.chave >= Ap->UU.U0.ri[k - 1].chave) 
			{
				valores->comp++;
				NaoAchouPosicao = 0;
				break;
			}
			Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k - 1];
			Ap->UU.U0.pi[k + 1] = Ap->UU.U0.pi[k];
			k--;
			if (k < 1)
				NaoAchouPosicao = 0;
		}
		Ap->UU.U0.ri[k] = Reg;
		Ap->UU.U0.pi[k + 1] = ApDir;
		Ap->UU.U0.ni++;
		return;
		
	}
        //caso contrario, (nó externo(folha)) busca na pagina onde o registro será inserido
	k = Ap->UU.U1.ne;
	NaoAchouPosicao = (k > 0);

	while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->UU.U1.re[k - 1].chave) 
        {
            valores->comp++;
            NaoAchouPosicao = 0;
            break;
        }
        Ap->UU.U1.re[k] = Ap->UU.U1.re[k - 1];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->UU.U1.re[k] = Reg;
    Ap->UU.U1.ne++;
}

void Ins(TRegistro Reg, TipoApontadorEstrela Ap, int *Cresceu, TRegistro *RegRetorno, TipoApontadorEstrela *ApRetorno, TAnalise *valores)
{
    TipoApontadorEstrela ApTemp,Pag;
    long i=1, j;
    Pag = Ap;
	int n;
	
	if (Ap == NULL) {
		*Cresceu = 1;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return;
	}
	
	//caminhamento em indices
	if (Ap->Pt == Interna){
		while (i < Pag->UU.U0.ni && Reg.chave > Pag->UU.U0.ri[i - 1].chave){
			i++;
			valores->comp++;
		}
		if (Reg.chave < Pag->UU.U0.ri[i - 1].chave)
		{
			valores->comp++;
			i--;
		}
		Ins(Reg, Pag->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno, valores);	
		return;
	
	
		if (!*Cresceu) {
			return;
		}
	
	//Overflow. Página interna (indice) precisa ser dividida (excedeu limite MM)
		ApTemp = (TipoApontadorEstrela) calloc(1, sizeof(TipoPaginaEstrela));
		ApTemp->UU.U0.ni = 0;
		ApTemp->UU.U0.pi[0] = NULL;

		if (i < M + 1){
			TRegistro RegTemp;
			RegTemp.chave = Ap->UU.U0.ri[MM - 1].chave;
			InsereNaPagina(ApTemp, RegTemp, Ap->UU.U0.pi[MM],valores);
			Ap->UU.U0.ni--;
			InsereNaPagina(Ap, *RegRetorno, *ApRetorno,valores);
		} 
		else{
			InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno,valores);
		}

		for (j = M + 2; j <= MM; j++) {
			TRegistro RegTemp;
			RegTemp.chave = Ap->UU.U0.ri[j - 1].chave;
			InsereNaPagina(ApTemp, RegTemp, Ap->UU.U0.pi[j],valores);
		}
		Ap->UU.U0.ni = M;
		ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[M + 1];
		(*RegRetorno).chave = Ap->UU.U0.ri[M].chave;
		*ApRetorno = ApTemp;
	}

    //em paginas folha
	while (i < Pag->UU.U1.ne && Reg.chave > Pag->UU.U1.re[i - 1].chave){
			i++;
			valores->comp++;
	}
	
	if (Reg.chave == Pag->UU.U1.re[i - 1].chave)
        {   
            valores->comp++;
            //O registro ja esta presente
            //*Cresceu = 0;
            return;
        }
	
	if (Reg.chave < Ap->UU.U1.re[i - 1].chave) {
		i--;
	}

	Ins(Reg,NULL,Cresceu,RegRetorno,ApRetorno,valores);
	if (!*Cresceu) {
		return;
	}
	
	if (Pag->UU.U1.ne < MM)
    {
		//Pagina tem espaco 
        valores->comp++;
        InsereNaPagina(Pag, *RegRetorno, *ApRetorno, valores);
        *Cresceu = 0;
        return;
    }
		
    //Overflow. Página externa (folha) precisa ser dividida (excedeu limite MM) 
    ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
    ApTemp->Pt = Externa;
	ApTemp->UU.U1.ne = 0;
    if (i <= M + 1)
    {
        InsereNaPagina(ApTemp, Ap->UU.U1.re[MM - 1], NULL, valores);
        Ap->UU.U1.ne--;
        InsereNaPagina(Pag, *RegRetorno, *ApRetorno, valores);
    }
    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, valores);
    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Pag->UU.U1.re[j - 1], Ap->UU.U0.pi[j], valores);
    Ap->UU.U1.ne = M;
    *RegRetorno = Ap->UU.U1.re[M];
	InsereNaPagina(ApTemp, Ap->UU.U1.re[M], NULL,valores);
    *ApRetorno = ApTemp;
} 
//Insere registro na arvore (onde sera inserido sera verificado no Ins)
void Insere(TRegistro Reg, TipoApontadorEstrela *Ap, TAnalise *valores)
{
    int Cresceu;
    TRegistro RegRetorno;
    TipoPaginaEstrela *ApRetorno, *ApTemp;
    
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, valores);

    if (Cresceu)   // Arvore cresce na altura pela raiz 
    {	
		ApTemp = (TipoPaginaEstrela*) malloc (sizeof(TipoPaginaEstrela));
        if(ApRetorno == NULL){
			ApTemp->Pt = Externa;
			ApTemp->UU.U1.ne = 1;
			ApTemp->UU.U1.re[0] = RegRetorno;
		}
		else{	
			ApTemp->Pt = Interna;
			ApTemp->UU.U0.ni = 1;
			ApTemp->UU.U0.ri[0] = RegRetorno;
			ApTemp->UU.U0.pi[1] = ApRetorno;
			ApTemp->UU.U0.pi[0] = *Ap;
		}
		*Ap = ApTemp;
	}
}
//Inicializa arvore b estrela
void ArvoreBE(FILE *arq, int chave)
{
    TipoApontadorEstrela Ap;
    TRegistro item;
    
    TAnalise valores;
    AnaliseInicia(&valores);
    
    Ap=(TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
    Inicializa (&Ap);
    while (fread(&item, sizeof(TRegistro), 1, arq) == 1)
    {
        valores.transf++;
        Insere(item, &Ap, &valores);
    }
    item.chave=chave;
    
    Pesquisa(&item , &Ap);
}

