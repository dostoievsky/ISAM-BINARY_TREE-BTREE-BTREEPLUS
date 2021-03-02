#include "ArvoreBE.h"

void Inicializa (TipoApontadorEstrela *Arvore)
{
    *Arvore = NULL;
}

//INICIALIZA, CONSTROI E ENTÃO REALIZA PESQUISA 
//NA ARVORE B ESTRELA
void ArvoreBE(FILE *arq, int chave)
{
		//APONTADOR DE INDICES, ARVORE EXTERNA DE INDICES
    TipoApontadorEstrela Ap;

		//REGISTRO QUE RECEBERÁ DO ARQUIVO PARA INSERIR EM ARVORE
    TRegistro item;
    
		//VALORES DE ANALISE DE COMPARAÇÕES E MOVIMENTO DE DADOS
    TAnalise valores;
    AnaliseInicia(&valores);
    
		//ALOCA MEMORIA PARA ARVORE
    Ap=(TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));

		//INICIALIZA ARVORE
    Inicializa (&Ap);

		//LE ARQUIVO E INSERE NA ARVORE
    while (fread(&item, sizeof(TRegistro), 1, arq) == 1)
    {
        valores.transf++;
        Insere(item, &Ap, &valores);
    }

		//VARIAVEL DE INSERÇÃO DE ITENS RECEBE A CHAVE PARA PESQUISA
    item.chave=chave;

    //VER ARVORE
    imprimeBStarTree(Ap, chave, &valores);
    
		//PESQUISA CHAVE NA ARVORE
    //Pesquisa(&item , &Ap, &valores);
}

//Insere registro na arvore (onde sera inserido sera verificado no Ins)
void Insere(const TRegistro& Reg, TipoApontadorEstrela *Ap, TAnalise *valores)
{
		//VARIAVEL PARA CONTROLAR O CRESCIMENTO DA ARVORE
    int Cresceu;
		//VARIAVEL DE INSERIR REGISTRO
    TRegistro RegRetorno;
		//PAGINA DE ARVORE E PAGINA TEMPORARIA PARA 
		//ACRESNTAR A ARVORE EM CASO DE CRESCIMENTO
    TipoPaginaEstrela *ApRetorno, *ApTemp;
    
		//FUNÇÃO DE INSERÇÃO PARA ARVORE
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, valores);

		//SE A ARVORE CRESCEU, CRESCE NA ALTURA DA RAIZ
		//E A ARVORE RECEBE NOVO REGISTRO
    if (Cresceu)   
    {	
		ApTemp = (TipoPaginaEstrela*) malloc (sizeof(TipoPaginaEstrela));
        if(ApRetorno == NULL){
			ApTemp->Pt = Externa;
			ApTemp->UU.U1.ne = 1;
			ApTemp->UU.U1.re[0] = RegRetorno;
		}
		else{	
			//SENÃO, ARVORE RECEBE APENAS REGISTRO
			//NA PAGINA INTERNA
			ApTemp->Pt = Interna;
			ApTemp->UU.U0.ni = 1;
			ApTemp->UU.U0.ri[0] = RegRetorno;
			ApTemp->UU.U0.pi[1] = ApRetorno;
			ApTemp->UU.U0.pi[0] = *Ap;
		}
		//ANEXA O DADO À ARVORE
		*Ap = ApTemp;
	}
}

void Ins(TRegistro Reg, TipoApontadorEstrela Ap, int *Cresceu, TRegistro *RegRetorno, TipoApontadorEstrela *ApRetorno, TAnalise *valores)
{
		//TIPOS TEMPORARIOS PARA INSERIR DADOS
    TipoApontadorEstrela ApTemp,Pag;
    long i=1, j;
		//PAGINA RECEBE ARVORE
    Pag = Ap;
	
	//SE A ARVORE AINDA É VAZIA, CRESCE
	//E ADICIONA O PRIMEIRO REGISTRO E
	//O PRIMEIRO INDICE
	if (Ap == NULL) {
		*Cresceu = 1;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return;
	}
	
	//SENÃO, CAMINHAMOS PELOS INDICES PARA
	//ENCONTRAR A POSIÇÃO
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
	
		//SENÃO CRESCEU, BASTA RETORNAMOS
		if (!*Cresceu) {
			return;
		}
	

	//SE CRESCEU, REALIZAMOS O OVERFLOW:
	//PAGINA DE INDICES PRECISA DE SER
	//DIVIDA
		ApTemp = (TipoApontadorEstrela) calloc(1, sizeof(TipoPaginaEstrela));
		ApTemp->UU.U0.ni = 0;
		ApTemp->UU.U0.pi[0] = NULL;

		if (i < M + 1){
			TRegistro RegTemp;
			RegTemp.dado1 = 0;
			RegTemp.dado2 = 0;

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
			RegTemp.dado1 = 0;
			RegTemp.dado2 = 0;

			RegTemp.chave = Ap->UU.U0.ri[j - 1].chave;
			InsereNaPagina(ApTemp, RegTemp, Ap->UU.U0.pi[j],valores);
		}
		Ap->UU.U0.ni = M;
		ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[M + 1];
		(*RegRetorno).chave = Ap->UU.U0.ri[M].chave;
		*ApRetorno = ApTemp;
	}

    //COMPARAÇÕES DE DADOS NA PAGINA FOLHA
	while (i < Pag->UU.U1.ne && Reg.chave > Pag->UU.U1.re[i - 1].chave){
		i++;
		valores->comp++;
	}
	
	//SE O REGISTRO JÁ ESTIVER PRESENTE, RETORNAMOS
	if (Reg.chave == Pag->UU.U1.re[i - 1].chave)
        {   
            valores->comp++;
            return;
        }
	
	//SENÃO, CONTINUAMOS A CAMINHAR
	if (Reg.chave < Ap->UU.U1.re[i - 1].chave) {
		i--;
	}

	//CHAMA RECURSIVA PARA ACESSAR OUTRA PAGINA
	Ins(Reg,NULL,Cresceu,RegRetorno,ApRetorno,valores);
	if (!*Cresceu) {
		return;
	}
	

	if (Pag->UU.U1.ne < MM)
    {
		//PAGINA TEM ESPAÇO 
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

void InsereNaPagina(TipoApontadorEstrela Ap, TRegistro Reg, TipoApontadorEstrela ApDir, TAnalise *valores)
{
	//INSERE REGISTRO NA PAGINA FOLHA, E NO INDICE, CASO SEJA TAMBÉM
	//UMA CHAVE DE INDICE
    int k;
    int NaoAchouPosicao;
		
		//CASO SEJA UM NÓ INTERNO (DE INDICE)
		//PESQUISA NA ARVORE O LOCAL DE
		//INSERÇÃO DO REGISTRO
    if(Ap->Pt == Interna)
		{ 
	
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

				if (k < 1) {
					NaoAchouPosicao = 0;
				}
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

void Pesquisa(TRegistro *x, TipoApontadorEstrela *Ap, TAnalise *valores) {
    int i;
    TipoApontadorEstrela Pag;
    Pag = *Ap;
    if ((*Ap)->Pt == Interna){
        i = 1;
        while (i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i - 1].chave) i++;
        if (x->chave < Pag->UU.U0.ri[i - 1].chave){
            Pesquisa(x, &Pag->UU.U0.pi[i - 1], valores);
        }
        else{
            Pesquisa(x, &Pag->UU.U0.pi[i], valores);
        }
        return;
    }
    i = 1;
    while(i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i - 1].chave) i++;

    if (x->chave == Pag->UU.U1.re[i - 1].chave){
        *x = Pag->UU.U1.re[i - 1];
        printf("chave encontrada!\n");
        printf("chave: %d.\n", x->chave);
        printf("Dado1: %.2lf\n", x->dado1);
        printf("Dado2: %ld\n", x->dado2);
        printf("Dado3: %s.\n", x->dado3);
        printf("\n Medidas\n");
				printf("Comparações: %d.\nTransferencias: %d.\n\n", valores->comp, valores->transf);
        return;
    }
		//SE NÃO, EXIBE MENSAGEM DE FALHA
    else
		{
			printf("TipoRegistro nao esta presente na arvore\n");
		}
}

void imprimeBStarTree(TipoApontadorEstrela Ap, int chave, TAnalise *valores)
{
		TRegistro encontrou;
    if (Ap == NULL)
        return;

    if(Ap->Pt == Interna)
    {
      int i = 0;
        while (i <= Ap->UU.U0.ni) {
          imprimeBStarTree(Ap->UU.U0.pi[i], chave, valores);
            //não acessar uma posição inválida
            if (i != Ap->UU.U0.ni)
								if (chave == Ap->UU.U0.ri[i].chave){
									cout << "encontrou interno!";
								}
                //printf("Interno : (%d) %d\n", i, Ap->UU.U0.ri[i].chave);
            i++;
        }
    }
    else
    {
    	//printf("Externo: ");
       TipoApontadorEstrela aux = Ap;
        for (int j = 0; j < Ap->UU.U1.ne; j++) {
					if (chave == aux->UU.U1.re[j].chave){
									encontrou = aux->UU.U1.re[j];
									printf("chave encontrada!\n");
        					printf("chave: %d.\n", encontrou.chave);
        					printf("Dado1: %.2lf\n", encontrou.dado1);
        					printf("Dado2: %ld\n", encontrou.dado2);
        					printf("Dado3: %s.\n", encontrou.dado3);
        					printf("\n Medidas\n");
									printf("Comparações: %d.\nTransferencias: %d.\n\n", valores->comp, valores->transf);
									return;
									//cout << "encontrou externo!";
					}
            //printf("(%d) %d ", j, aux->UU.U1.re[j].chave);
        }
      	//printf("\n");
    }
}