#include <stdio.h> #include <stdlib.h> #include <time.h> #include <string.h>

#define N 100000     // Tamanho do vetor #define RODADAS 10   // Quantidade de rodadas de execução

// Gera valores aleatórios no vetor void gerar_aleatorio(int vet[], int tam) { for (int i = 0; i < tam; i++) { vet[i] = rand() % 1000000 + 1; } }

// Copia os valores de um vetor para outro void copiar_vetor(int origem[], int destino[], int tam) { memcpy(destino, origem, tam * sizeof(int)); }

// Algoritmo Bubble Sort void bubble_sort(int vet[], int tam) { for (int i = 0; i < tam - 1; i++) { for (int j = 0; j < tam - i - 1; j++) { if (vet[j] > vet[j + 1]) { int aux = vet[j]; vet[j] = vet[j + 1]; vet[j + 1] = aux; } } } }

// Algoritmo Insertion Sort void insertion_sort(int vet[], int tam) { for (int i = 1; i < tam; i++) { int chave = vet[i]; int j = i - 1; while (j >= 0 && vet[j] > chave) { vet[j + 1] = vet[j]; j--; } vet[j + 1] = chave; } }

// Algoritmo Selection Sort void selection_sort(int vet[], int tam) { for (int i = 0; i < tam - 1; i++) { int min = i; for (int j = i + 1; j < tam; j++) { if (vet[j] < vet[min]) { min = j; } } int aux = vet[i]; vet[i] = vet[min]; vet[min] = aux; } }

// Algoritmo Quick Sort (recursivo) void quick_sort(int vet[], int inicio, int fim) { if (inicio < fim) { int pivo = vet[fim]; int i = inicio - 1; for (int j = inicio; j < fim; j++) { if (vet[j] <= pivo) { i++; int aux = vet[i]; vet[i] = vet[j]; vet[j] = aux; } } int aux = vet[i + 1]; vet[i + 1] = vet[fim]; vet[fim] = aux; quick_sort(vet, inicio, i); quick_sort(vet, i + 2, fim); } }

// Funções auxiliares para o Merge Sort void merge(int vet[], int inicio, int meio, int fim) { int n1 = meio - inicio + 1; int n2 = fim - meio;

int *L = malloc(n1 * sizeof(int));
int *R = malloc(n2 * sizeof(int));

for (int i = 0; i < n1; i++) L[i] = vet[inicio + i];
for (int j = 0; j < n2; j++) R[j] = vet[meio + 1 + j];

int i = 0, j = 0, k = inicio;
while (i < n1 && j < n2) {
    if (L[i] <= R[j]) vet[k++] = L[i++];
    else vet[k++] = R[j++];
}

while (i < n1) vet[k++] = L[i++];
while (j < n2) vet[k++] = R[j++];

free(L);
free(R);

}

void merge_sort(int vet[], int inicio, int fim) { if (inicio < fim) { int meio = (inicio + fim) / 2; merge_sort(vet, inicio, meio); merge_sort(vet, meio + 1, fim); merge(vet, inicio, meio, fim); } }

// Funções para medir tempo de execução de cada algoritmo double tempo_bubble(int vet[], int tam) { clock_t ini = clock(); bubble_sort(vet, tam); return (double)(clock() - ini) / CLOCKS_PER_SEC; }

double tempo_insertion(int vet[], int tam) { clock_t ini = clock(); insertion_sort(vet, tam); return (double)(clock() - ini) / CLOCKS_PER_SEC; }

double tempo_selection(int vet[], int tam) { clock_t ini = clock(); selection_sort(vet, tam); return (double)(clock() - ini) / CLOCKS_PER_SEC; }

double tempo_quick(int vet[], int tam) { clock_t ini = clock(); quick_sort(vet, 0, tam - 1); return (double)(clock() - ini) / CLOCKS_PER_SEC; }

double tempo_merge(int vet[], int tam) { clock_t ini = clock(); merge_sort(vet, 0, tam - 1); return (double)(clock() - ini) / CLOCKS_PER_SEC; }

// Função principal int main() { srand(time(NULL));

int original[N], copia[N];
double tempo_b[RODADAS], tempo_i[RODADAS], tempo_s[RODADAS], tempo_q[RODADAS], tempo_m[RODADAS];

// Executa 10 rodadas
for (int r = 0; r < RODADAS; r++) {
    printf("Executando rodada %d...\n", r + 1);

    gerar_aleatorio(original, N);

    copiar_vetor(original, copia, N);
    tempo_b[r] = tempo_bubble(copia, N);

    copiar_vetor(original, copia, N);
    tempo_i[r] = tempo_insertion(copia, N);

    copiar_vetor(original, copia, N);
    tempo_s[r] = tempo_selection(copia, N);

    copiar_vetor(original, copia, N);
    tempo_q[r] = tempo_quick(copia, N);

    copiar_vetor(original, copia, N);
    tempo_m[r] = tempo_merge(copia, N);
}

// Cálculo das médias
double soma_b = 0, soma_i = 0, soma_s = 0, soma_q = 0, soma_m = 0;

for (int i = 0; i < RODADAS; i++) {
    printf("Rodada %d:\n", i + 1);
    printf("Bubble: %.3f s | Insertion: %.3f s | Selection: %.3f s | Quick: %.3f s | Merge: %.3f s\n\n",
           tempo_b[i], tempo_i[i], tempo_s[i], tempo_q[i], tempo_m[i]);

    soma_b += tempo_b[i];
    soma_i += tempo_i[i];
    soma_s += tempo_s[i];
    soma_q += tempo_q[i];
    soma_m += tempo_m[i];
}

// Mostra as médias
printf("Médias:\n");
printf("Bubble: %.3f s\n", soma_b / RODADAS);
printf("Insertion: %.3f s\n", soma_i / RODADAS);
printf("Selection: %.3f s\n", soma_s / RODADAS);
printf("Quick: %.3f s\n", soma_q / RODADAS);
printf("Merge: %.3f s\n", soma_m / RODADAS);

return 0;

}

