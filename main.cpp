/* 
 * File:   main.cpp
 */

#include "Tp1.h"
#include "PesquisaSequencial.h"
#include "ArvoreBinaria.h"
#include "ArvoreB.h"
#include "ArvoreBE.h"


/*
 * 
 */

int main(int argc, char** argv) {

    FILE *arq = new FILE;
    TRegistro x;
    
    time_t start,end;

    int n, situacao, metodo;

    metodo = atoi(argv[1]);
    n = atoi(argv[2]);
    situacao = atoi(argv[3]);
    x.chave = atoi(argv[4]);

    if (metodo< 1 || metodo> 4)
    {
        printf("Metodo errado (1~4)!\n");
        return 0;
    }
    if (situacao <1 || situacao >3)
    {
        printf("Situacao errada (1~3)!\n");
        return 0;
    }
    
    if(!(GeraArquivo(arq, situacao, n)))
    {
        printf("Erro ao criar arquivo!\n");
        return 0;
    }
    if((arq=fopen("teste.bin","rb"))==NULL)
    {
        printf("Nao foi possivel ler o arquivo!\n");
        return 0;
    }

    //Pesquisa Sequencial Indexada
    if (metodo == 1) {
        int maxtabela = n/ITENSPAGINA;
        start=clock();
        PesquisaSequencial(&x, arq, maxtabela);
        end=clock();
        printf ("Tempo gasto %f milisegundos\n",((double)( end - start ) / ((double)CLOCKS_PER_SEC )));
    }
    
    //Arvore Binaria de Pesquisa
    if (metodo == 2) {
        start=clock();
        ArvoreBinaria(arq, x);
        end=clock();
        printf ("Tempo gasto %f milisegundos\n",((double)( end - start ) / ((double)CLOCKS_PER_SEC )));
    }
    
    //Arvore B
    if(metodo == 3){
        start=clock();
        ArvoreB(arq, x.chave);
        end=clock();
        printf ("Tempo gasto %f milisegundos\n",((double)( end - start ) / ((double)CLOCKS_PER_SEC )));
    }
    
    //ArvoreBE
    if(metodo ==4){
        start=clock();
        ArvoreBE(arq,x.chave);
        end=clock();
        printf ("Tempo gasto %f milisegundos\n",((double)( end - start ) / ((double)CLOCKS_PER_SEC )));
    }
    
    
    //Verifica -P
    if(argc == 6)
    {
        if(strcmp(argv[5],"-P")==0)
            Imprime(arq);
    }

}
