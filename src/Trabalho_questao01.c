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

int main(){
    srand(time(NULL));

    double tempos_sequencial[30], tempos_binaria[30];
    double soma_sequencial = 0, soma_binaria = 0;

    //Busca sequencial 30 vezes
    for(int i=0; i<30; i++){
        int vet_sequencial[N];
        gerar_aleatorio(vet_sequencial, N); //Gera vetor aleatorio
        int valor_busca = rand() % 1000000 + 1; //Gera valor aleatorio
        tempos_sequencial[i] = tempo_execucao(busca_sequencial, vet_sequencial, N, valor_busca);
        soma_sequencial += tempos_sequencial[i];
    }
    //Busca binaria 30 vezes
    for(int i=0; i<30; i++){
        int vet_binario[N];
        gerar_aleatorio(vet_binario, N); //Gera vetor aleatorio
        ordenar(vet_binario, N); //Ordena vetor
        int valor_busca = rand() % 1000000 + 1; //Gera valor aleatorio
        tempos_binaria[i] = tempo_execucao(busca_binaria, vet_binario, N, valor_busca);
        soma_binaria += tempos_binaria[i];
    }

    //Calcular a media sequencial
    double media_sequencial = soma_sequencial / I;

    //Calcular desvio padrao sequencial
    double soma_quadrados_sequencial = 0;
    for(int i=0; i<I; i++){
        soma_quadrados_sequencial += pow(tempos_sequencial[i] - media_sequencial, 2);
    }
    double desvio_sequencial = sqrt(soma_quadrados_sequencial / I);

    //Calcular a media binaria
    double media_binaria = soma_binaria / I;

    //Calcular desvio padrao binario
    double soma_quadrados_binario = 0;
    for(int i=0; i<I; i++){
        soma_quadrados_binario += pow(tempos_binaria[i] - media_binaria, 2);
    }
    double desvio_binario = sqrt(soma_quadrados_binario / I);

    //Exibição de teste
    printf("Busca Sequencial: \n");
    printf("Media do tempo: %.6f s\n", media_sequencial);
    printf("Desvio Padrao: %.6f s\n\n", desvio_sequencial);

    printf("Busca Binaria: \n");
    printf("Media do tempo: %.6f s\n", media_binaria);
    printf("Desvio Padrao: %.6f s\n\n", desvio_binario);

    return 0;
}