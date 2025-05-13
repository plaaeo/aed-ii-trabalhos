#include <stdio.h>
#include <stdlib.h>

#include "../pct.h"

void questao2(unsigned int seed) {
  Pacote pacotes[N];
    abp_pct_t* raiz;

    for(int i=0; i<N; i++){

        //gera pacote
        pacotes[i].id = rand() % 10000;       
        srand(pacotes[i].id);
        pacotes[i].dado = (rand() % 26) + 97;

        //inserir o pacote criado
        pct_abp_inserir(raiz, pacotes[i]);
    }

    
    //salvar dados em um arquivo
    FILE *q2csv = fopen("q2.csv", "w");
        if(q2csv) {
            printf("  (escrevendo dados da questao 2 em 'q2.csv')\n");
            
            // Imprimir dados em formato csv
            fprintf(q2csv, "ID,Dado\n");

            pct_ordenar_id(pacotes, N);
            for(int i = 0; i < 20; i++){
                fprintf(q2csv, "%d,%s\n", pacotes[i].id, pacotes[i].dado);
            }
            fclose(q2csv);
        }
};
