#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <limits.h>
#include "../abp.h"
#include "../vetor.h"

#define TAMANHO 1000000
#define BUSCAS 30

long obter_uso_memoria() {
    struct rusage uso;
    getrusage(RUSAGE_SELF, &uso);
    return uso.ru_maxrss;
}

// TODO: pausas para verificar o gerenciador de tarefas
// TODO: inserir na árvore binária usando caminhamento binário no vetor
//       (mto role) mas da pra fazer
void questao3(unsigned int seed) {
    srand(time(NULL));
    long memoria_minima = LONG_MAX;
    long memoria_maxima = 0;
    
    // Alocação com verificação
    vetor_t vetor = (vetor_t) malloc(TAMANHO * sizeof(int));
    vetor_t vetor_ordenado = (vetor_t) malloc(TAMANHO * sizeof(int));

    if (!vetor || !vetor_ordenado) {
        perror("Erro na alocação de memória");
        exit(EXIT_FAILURE);
    }
    
    abp_t* arvore = NULL;

    printf("Gerando dados...\n");
    vetor_gerar_aleatorio(vetor, TAMANHO);
    vetor_copiar(vetor, vetor_ordenado, TAMANHO);
    
    printf("Ordenando vetor...\n");
    vetor_ordenar_merge(vetor_ordenado, 0, TAMANHO);

    printf("Construindo ABP...\n");
    for (int i = 0; i < TAMANHO; i++) {
        arvore = abp_inserir(arvore, vetor[i]);
        if (i % 100000 == 0) printf("."); // Progresso
    }
    printf("\n");
    
    // Preparar buscas - garantindo que alguns valores existam e outros não
    int valores_busca[BUSCAS];
    for (int i = 0; i < BUSCAS; i++) {
        if (i % 3 == 0) {
            // Valores que existem no vetor
            valores_busca[i] = vetor_ordenado[rand() % TAMANHO];
        } else if (i % 3 == 1) {
            // Valores que existem na ABP mas podem não estar no vetor
            valores_busca[i] = vetor[rand() % TAMANHO];
        } else {
            // Valores que não existem
            valores_busca[i] = (2 * TAMANHO) + (rand() % TAMANHO);
        }
    }

    double tempo_total_abb = 0;
    double tempo_total_vetor = 0;
    
    printf("Executando buscas...\n");
    for (int i = 0; i < BUSCAS; i++) {
        int valor = valores_busca[i];
        
        long memoria_antes = obter_uso_memoria();
        
        // Busca na ABP
        clock_t inicio = clock();
        abp_t* resultado_abb = abp_buscar(arvore, valor);
        clock_t fim = clock();
        double tempo_abb = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
        tempo_total_abb += tempo_abb;
        
        // Busca no vetor
        inicio = clock();
        int resultado_vetor = vetor_busca_binaria(vetor_ordenado, TAMANHO, valor);
        fim = clock();
        double tempo_vetor = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
        tempo_total_vetor += tempo_vetor;
        
        // Verificação de consistência
        int encontrado_abb = (resultado_abb != NULL);
        int encontrado_vetor = (resultado_vetor != -1);
        
        if (encontrado_abb != encontrado_vetor) {
            printf("Aviso: divergência na busca por %d (ABP: %d, Vetor: %d)\n", 
                  valor, encontrado_abb, encontrado_vetor);
        }
        
        long memoria_depois = obter_uso_memoria();
        
        memoria_minima = (memoria_antes < memoria_minima) ? memoria_antes : memoria_minima;
        memoria_minima = (memoria_depois < memoria_minima) ? memoria_depois : memoria_minima;
        memoria_maxima = (memoria_antes > memoria_maxima) ? memoria_antes : memoria_maxima;
        memoria_maxima = (memoria_depois > memoria_maxima) ? memoria_depois : memoria_maxima;
        
        printf("Busca %2d: ABP=%7.3fms | Vetor=%7.3fms | Mem=%ldKB | Valor=%d\n", 
              i+1, tempo_abb, tempo_vetor, memoria_depois, valor);
    }
    
    printf("\nRESULTADOS FINAIS:\n");
    printf("Tempo médio ABP: %.3f ms\n", tempo_total_abb / BUSCAS);
    printf("Tempo médio Vetor: %.3f ms\n", tempo_total_vetor / BUSCAS);
    printf("Uso mínimo de memória: %ld KB\n", memoria_minima);
    printf("Uso máximo de memória: %ld KB\n", memoria_maxima);
    printf("Altura da ABP: %d\n", abp_altura(arvore));
    
    abp_liberar(arvore);
    free(vetor);
    free(vetor_ordenado);
}