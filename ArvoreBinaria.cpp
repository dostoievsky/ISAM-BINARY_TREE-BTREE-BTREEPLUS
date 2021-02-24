#include <stdio.h>
#include "Tp1.h"
#include "ArvoreBinaria.h"

void ArvoreBinaria(FILE *arq, TRegistro chave)
 {

    FILE *tabela;

    TAnalise valores;

    TRegistro item;

    AnaliseInicia(&valores);
    
    if ((tabela = fopen("tabela.bin", "w+b")) == NULL)
    {

        printf("Nao foi possivel criar a tabela de indices da arvore.\n");

        return;

    }

    GeraTabela(arq, tabela, &valores);

    if ((tabela = fopen("tabela.bin", "rb")) == NULL)
    {

        printf("Nao foi possivel ler a tabela de indices da arvore binaria.\n");

        return;

    }

    printf("Comparacoes geracao: %d\n", valores.comp);

    PesquisaArvoreBin(tabela, chave.chave, 0, arq, &item, &valores);
        
    printf("Chave: %d.\n", item.chave);
    printf("Dado1: %.2lf\n", item.dado1);
    printf("Dado2: %ld\n", item.dado2);
    printf("Dado3: %s.\n", item.dado3);
    printf("\n Medidas\n");
    printf("Comparações: %d.\nTransferencias: %d.\n\n", valores.comp, valores.transf);
    
    fclose(tabela);
    fclose(arq);

}

void GeraTabela(FILE *arq, FILE *tabela, TAnalise *valores)
 {

    TNo no;

    int indice = 0;

    TRegistro item;

    int desloc;

    while (fread(&item, sizeof (TRegistro), 1, arq) == 1)
    {

        valores->transf++;

        no.chave = item.chave;

        no.pEsq = -1;

        no.pDir = -1;

        desloc = (indice * sizeof (TNo));

        fseek(tabela, desloc, 0);

        fwrite(&no, sizeof (TNo), 1, tabela);
        valores->transf++;
        rewind(tabela);

        // Verifica tabela de indices em cada inserção

        VerificaTabela(tabela, &indice, no.chave, 0, valores);

        indice++;

    }

    fclose(tabela);

}

void VerificaTabela(FILE *tabela, int *indice, int chave, int index, TAnalise *valores) // index = indice da tbl
 {

    TNo nodo;

    int desloc;

    desloc = index * sizeof (TNo);

    fseek(tabela, desloc, 0);

    fread(&nodo, sizeof (TNo), 1, tabela);
    
    valores->transf++;
    valores->comp++;

    if (chave < nodo.chave)
    {

        valores->comp++;

        if (nodo.pEsq == -1)
        {

            nodo.pEsq = (*indice);

            fseek(tabela, desloc, 0);

            fwrite(&nodo, sizeof (TNo), 1, tabela);
            valores->transf++;

        }
        else
        {

            index = nodo.pEsq;

            VerificaTabela(tabela, indice, chave, index, valores);

        }

    }
    if (chave > nodo.chave)
    {

        valores->comp++;

        if (nodo.pDir == -1)
        {
            nodo.pDir = (*indice);
            fseek(tabela, desloc, 0);
            fwrite(&nodo, sizeof (TNo), 1, tabela);
            valores->transf++;

        }
        else
        {
            index = nodo.pDir;
            VerificaTabela(tabela, indice, chave, index, valores);

        }

    }

}

int PesquisaArvoreBin(FILE *tabela, int chave, int index, FILE *arq, TRegistro *item, TAnalise *valores)
 {

    TNo nodo;

    int desloc;

    desloc = index * sizeof (TNo);

    fseek(tabela, desloc, 0);

    fread(&nodo, sizeof (TNo), 1, tabela);
    valores->transf++;

    valores->comp++;
    if (chave < nodo.chave)
    {
        index = nodo.pEsq;
        PesquisaArvoreBin(tabela, chave, index, arq, item, valores);

    }
    else if (chave > nodo.chave)
    {
        index = nodo.pDir;
        PesquisaArvoreBin(tabela, chave, index, arq, item, valores);

    }
    else
    {
        desloc = index * sizeof (TRegistro);
        rewind(arq);
        fseek(arq, desloc, 0);
        if (fread(item, sizeof (TRegistro), 1, arq) == 1)
        {
            valores->transf++;
            printf("Chave encontrada ! \n");
            
            return 1;
        }
    }
    return 0;
}
