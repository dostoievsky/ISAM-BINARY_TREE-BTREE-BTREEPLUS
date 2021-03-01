//INCLUSÃO DO HEADER
#include "Tp1.h"


int GeraArquivo(FILE *arq,int situacao, int n)
{
    //VARIAVEIS DE USO
    TRegistro x;
    int i,k;
    
    //ABERTURA DO ARQUIVO
    if((arq = fopen("teste.bin", "wb")) == NULL)
    {
        printf("Nao foi possivel criar o arquivo.\n");
        return 0;
    }

    //DEFINE A ORDEM PARA O ARGUMENTO <SITUAÇÃO>
    switch (situacao)
    {
        // SITUAÇÃO ORDENADA (ARGUMENTO 1)
        case 1:
        {
            //GERA EM ORDEM CRESCENTE DE 0 A N
            for(i=0; i<n; i++)
            {
                //CHAVE RECEBECE i (INICIALIZADO EM 0) + 1
                //OU SEJA, EXISTEM N CHAVES DE VALOR 1...N
                x.chave = i+1;
                //k RECEBE UM VALOR ALEATORIO DE 0 A 100
                k = rand()%100;
                //x.dado1 RECEBE UM HASH /7 DE K
                x.dado1 = (k/7);
                //x.dado2 RECEBE UM VALOR ALEATORIO ENORME
                x.dado2 = (long int) rand()%99999999999;
                //x.dado3 RECEBE A CHAVE E É CONCATENADO COM UMA IDENTIFICAÇÃO
                sprintf(x.dado3, "%d", x.chave);
                strcat(x.dado3, "_universidadefederaldeouropreto");
                //ESCRITA DO REGISTRO EM ARQUIVO
                fwrite(&x, sizeof(TRegistro), 1, arq);
            }break;
        }
        case 2:
        {
            //GERA EM ORDEM DECRESCENTE DE N A 0
            //A ATRIBUIÇÃO DE VALORES É IDENTICA
            //AO CASO ORDENADO, SENDO APENAS
            //INICIALIZADA DO FIM ATÉ O INICIO
            for(i=n; i > 0; i--)
            {
                x.chave = i;
                k = rand()%100;
                x.dado1 = (k/7);
                x.dado2 = (long int) rand()%99999999999;
                sprintf(x.dado3, "%d", x.chave);
                strcat(x.dado3, "_universidadefederaldeouropreto");
                fwrite(&x, sizeof(TRegistro), 1, arq);
            }
            break;
        }
        case 3:
        {
            //GERA UM ARQUIVO DE ORDEM N EM SITUAÇÃO ALEATORIA

            //VETOR DE TRegistro QUE SERÁ O EMBARALHADOR DE NOSSO
            //CASO ALEATORIO COM TAMANHO N
            vector<TRegistro> embaralhador(n);

            //SEMENTE DE TEMPO EM QUE OS VALORES SERAO EMBARALHADOS
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

            //ESSE FOR É IDENTICO AO DO METODO CRESCENTE, POREM
            //O ARQUIVO NÃO RECEBERÁ O REGISTRO, MAS SIM O NOSSO VETOR
            // DE REGISTROS
            for(i=0; i<n; i++)
            {
                x.chave = i;
                k = rand()%100;
                x.dado1 = (k/7);
                x.dado2 = (long int) rand()%99999999999;
                sprintf(x.dado3, "%d", x.chave);
                strcat(x.dado3, "_universidadefederaldeouropreto");
                //VETOR DE REGISTROS EMBARALHADOR RECEBE O DADO:
                embaralhador[i] = x;
            }
            //FUNÇÃO SUFFLE C++ EMBARALHA TODOS OS DADOS DO VETOR 
            shuffle (embaralhador.begin(), embaralhador.end(), default_random_engine(seed));

            //APOS EMBARALHAR ATRIBUIMOS OS VALORES AO ARQUIVO
            for(i=0; i<n; i++)
            {
              fwrite(&embaralhador[i], sizeof(TRegistro), 1, arq); 
            }
            //LIBERA MEMORIA
            embaralhador.clear();
        break;
        }
    }
    //FECHA ARQUIVO
    fclose(arq);
    return 1;
}
void AnaliseInicia(TAnalise *valores)
{
    valores->comp=0;
    valores->transf=0;
}

void Imprime(FILE *arq)
{
    //ARGUMENTO -P
    TRegistro x;
    
    printf("Registros: \n\n");
    rewind(arq);
    while(fread(&x,sizeof(TRegistro),1,arq)==1)
    {
        printf("Chave: %d\n",x.chave);
        printf("Dado1: %lf\n",x.dado1);
        printf("Dado2: %ld\n",x.dado2);
        printf("Dado3: %s\n",x.dado3);
    }
}