//Desenvolva um programa que implemente um vetor com 1.000.000 (um milhão) de elementos do tipo inteiro. 
//Execute a busca sequencial no vetor com valores aleatórios desordenados e a busca binária no vetor com valores aleatórios ordenados. 
//Execute cada algoritmo 30 vezes. 
//Calcule e mostre o tempo de execução para cada busca, a média entre as 30 execuções e o desvio padrão dos tempos de execução para cada algoritmo.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 1000000 //Tamanho do Vetor

//Gerar vetor com valores aleatórios
void gerar_aleatorio(int vet[], int tam){
    for(int i=0; i<tam; i++){
        vet[i] = rand() % 1000000 + 1; //Valores aleatórios entre 1 e 1 milhão
    }
}

//Ordenar vetor
void ordenar(int vet[], int tam){
    for(int i=0; i<tam-1; i++){
        for(j = i+1; j<tam; j++){
            if(vet[i] > vet[j]){
                int aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

//Buscas
int busca_sequencial(int vet[], int tam, int valor){
    for(int i=0; i<tam; i++){
        if(vetor[i] == valor){
            return i; //Posição do valor
        }
    }
    return -1; //Caso não encontrar
}

int busca_binaria(int vet[], int tam, int valor){
    int x = 0, y = tam-1;
    while(x<=y){
        int meio = (x+y)/2;
        if(vet[meio] == valor){
            return meio; //Posição do valor
        }
        else if(vet[meio] < valor){
            x = meio+1;
        }
        else{
            y = meio-1;
        }
    }
    return -1; //Caso não encontrar
}

//Tempo de Execução
double tempo_execucao(void (*funcao)(int[], int, int), int vet[], int tam, int valor){
    clock_t inicio = clock();
    funcao(vet, tam, valor);
    clock_t fim = clock();
    return ((double)(fim-inicio)) / CLOCKS_PER_SEC;
}
