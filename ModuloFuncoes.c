#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "ModuloFuncoes.h"

int menu(){
    int op;
    printf("Digite as opção desejada\n");
    printf("0 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Excluir\n");
    printf("3 - Listar\n");
    printf("4 - Redimensionar Espaço\n");
    printf("5 - Lista Vetor Auxiliar Ordenado\n");
    printf("6 - Lista todos os elementos ordenados\n");
    scanf("%d", &op);
    return op;
}

void alocarMemoria(VetorPrincipal *vet,int indice){
    vet[indice].auxiliar = (int*)malloc(sizeof(int)*(vet[indice].tamanho));
    if (vet[indice].auxiliar == NULL){
        exit(1);
    }

}

void realocarMemoria(VetorPrincipal *vet, int indice){
    vet[indice].auxiliar = (int*)realloc(vet[indice].auxiliar,vet[indice].tamanho*sizeof(int));
    if(vet[indice].auxiliar == NULL){
        exit(1);
    }
}

void apagaValorMemoria(VetorPrincipal *vet,int i, int valor){
    int *v = (int *)malloc((vet[i].cont - 1) * sizeof(int));

    int find = 0;

    for (int j = 0, l = 0; j < vet[i].cont; j++) {
        if (vet[i].auxiliar[j] != valor)
            v[l++] = vet[i].auxiliar[j];
        else
            find = 1;
    }

    if (find) {
        vet[i].cont--;

        free(vet[i].auxiliar);

        vet[i].auxiliar = v;
    }
    else
        free(v);
}

void listaVetor(VetorPrincipal *vet, int i){
    printf("Temos %d elementos neste vetor.\n",vet[i].cont);
    for(int j=0;j<vet[i].cont;j++){
        printf("Valor: %d \n",vet[i].auxiliar[j]);
    }
}

void inserirValor(VetorPrincipal *vet, int i, int valor){
    vet[i].auxiliar[vet[i].cont]= valor;
    vet[i].cont = vet[i].cont + 1;
}

void transfereConteudo(VetorPrincipal *vet,int i,int *vetorAlvo){
    for(int j=0;j<vet[i].cont;j++){
        vetorAlvo[j] = vet[i].auxiliar[j];
    }
}

void insertionSort(int *vetor, int tamanho){
    int i, j, aux;
    for(i=1;i<tamanho;i++){
        aux=vetor[i];
        for(j=i-1;(j>=0)&&(aux<vetor[j]);j--){
            vetor[j+1]=vetor[j];
        }
        vetor[j+1]=aux;
    }
}

void listaVetorInt(int *vetor,int quantidade){
    for(int i =0;i<quantidade;i++){
        printf("%d\n",vetor[i]);
    }
}

void gravaArquivo(VetorPrincipal *vet){
    FILE *arq;
    arq = fopen("atv3.txt","w");
    //INDICE,QUANTIDADE DE ELEMENTOS,VALORES
    if (arq==NULL)
        printf("Erro na abertura do arquivo\n");
    else{
        for(int i=0;i<10;i++){
            if (vet[i].auxiliar != NULL){
                //salva posição
                fprintf(arq, "%d",i);
                //salva quant elementos para alocar
                fprintf(arq, "%d",vet[i].cont);
                for(int j=0;j<vet[i].cont;j++){
                    fprintf(arq,"%d",vet[i].auxiliar[j]);
                }
            }
        }
    }
    fclose(arq);
}

int lerArquivo(VetorPrincipal *vet){
    FILE *arq;
    int ind,qtd;
    arq = fopen("atv3.txt","r");
    if (arq==NULL){
        return 0;
    }
    else
    {
        while(!feof(arq)){
            ind = qtd = 0;
            //lê a posição que vai alocar
            fscanf(arq,"%d",&ind);
            //lê a quantidade de espaço alocado
            fscanf(arq,"%d",&qtd);
            vet[ind].auxiliar = (int *)malloc(sizeof(int)*qtd);
            for(int i=0;i<qtd;i++){
                fscanf(arq,"%d",&vet[ind].auxiliar[i]);
            }
        }
        return 1;
    }
    fclose(arq);
}
