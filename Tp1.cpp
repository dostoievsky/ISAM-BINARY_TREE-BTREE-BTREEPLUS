#include "Tp1.h"

int GeraArquivo(FILE *arq,int situacao, int n)
{
    TRegistro x;
    int i,k;
    
    if((arq = fopen("teste.bin", "wb")) == NULL)

    {
        printf("Nao foi possivel criar o arquivo.\n");
        return 0;
    }
    switch (situacao)
    {
        case 1:
        {
            for(i=0; i<n; i++)
            {
                x.chave = i+1;
                k = rand()%100;
                x.dado1 = (k/7);
                x.dado2 = (long int) rand()%99999999999;
                sprintf(x.dado3, "%d", x.chave);
                strcat(x.dado3, "_universidadefederaldeouropreto");
                fwrite(&x, sizeof(TRegistro), 1, arq);
            }break;
        }
        case 2:
        {
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
            vector<TRegistro> embaralhador(n);
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            for(i=0; i<n; i++)
            {
                x.chave = i;
                k = rand()%100;
                x.dado1 = (k/7);
                x.dado2 = (long int) rand()%99999999999;
                sprintf(x.dado3, "%d", x.chave);
                strcat(x.dado3, "_universidadefederaldeouropreto");
                embaralhador[i] = x;
            }
            shuffle (embaralhador.begin(), embaralhador.end(), default_random_engine(seed));
            //shuffle(embaralhador.begin(), embaralhador.end());
            for(i=0; i<n; i++)
            {
              fwrite(&embaralhador[i], sizeof(TRegistro), 1, arq); 
            }
            embaralhador.clear();
        break;
        }
    }
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