#include <stdio.h>
#include <stdlib.h>
#include "Tp1.h"
#include "PesquisaSequencial.h"

void PesquisaSequencial(TRegistro *item, FILE *arq, int maxtabela) 
{

    TIndice tabela[maxtabela];
    TAnalise valores;
    
    AnaliseInicia(&valores);

    // Gera Tabela

    TRegistro x;

    int cont = 0;
    int pos = 0;

    while (fread(&x, sizeof (TRegistro), 1, arq) == 1) {
        valores.transf++;
        cont++;
        if (cont % ITENSPAGINA == 1) {
            tabela[pos].chave = x.chave;
            tabela[pos].posicao = pos + 1;
            pos++;
        }
    }
    // Pesquisa Sequencial Indexada

    if (PesqSeqIndex(&tabela[0], pos, item, arq, &valores)) {
        printf("Chave encontrada!\n");
        printf("Chave: %d.\n", item->chave);
        printf("Dado1: %.2lf\n", item->dado1);
        printf("Dado2: %ld\n", item->dado2);
        printf("Dado3: %s.\n", item->dado3);
        printf("\n Medidas\n");
        printf("Comparações: %d.\nTransferencias: %d.\n\n", valores.comp, valores.transf);

    }

}

int PesqSeqIndex(TIndice *tabela, int tam, TRegistro *item, FILE *arq, TAnalise *valores)
 {

    TRegistro pagina[ITENSPAGINA];

    int i = 0;

    int quantitens;

    long desloc;

    while (i < tam && tabela[i].chave <= item->chave)
    {

        i++;

        valores->comp++;

    }

    if (i == 0)

        return 0;

    else
    {
        //ultima pagina pode nao estar completa
        if (i < tam)

            quantitens = ITENSPAGINA;

        else
        {

            fseek(arq, 0, SEEK_END);

            quantitens = (ftell(arq) / sizeof (TRegistro)) % ITENSPAGINA;

            if (quantitens == 0)
            {

                quantitens = ITENSPAGINA;

            }

        }

    }

    //le pagina desejada

    desloc = (tabela[i - 1].posicao - 1) * ITENSPAGINA * sizeof (TRegistro);

    fseek(arq, desloc, SEEK_SET);

    fread(&pagina, sizeof (TRegistro), quantitens, arq);

    valores->transf++;

    //pesquisa sequencial na pagina

    for (i = 0; i < quantitens; i++)
    {
        valores->comp++;
        if (pagina[i].chave == item->chave)
        {

            *item = pagina[i];

            return 1;

        }
    }
    return 0;
}
