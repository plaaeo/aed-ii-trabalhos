#include <stdio.h>
#include <stdlib.h>

#include "../pct.h"

void questao2() {
  Pacote pacotes[N];
  abp_pct_t* raiz = NULL;

  for(int i=0; i<N; i++){

    //gera pacote
    pacotes[i].id = rand() % 10000;       
    srand(pacotes[i].id);    
    pacotes[i].dado = (rand() % 26) + 97;
  }

  //ordena parcialmente os pacotes
  pct_ordenar_parcial_id(N, pacotes);
  
  for(int i=0; i<N; i++){
    //inserir o pacote criado
    raiz = pct_abp_inserir(raiz, pacotes[i]);
  }

  for(int i = 0; i < 20; i++){
    printf("%d,%c\n", pacotes[i].id, pacotes[i].dado);
  }
  printf("\n\n\n");
    
  pct_ordenar_id(N, pacotes);
    
  for(int i = 0; i < 20; i++){
    printf("%d,%c\n", pacotes[i].id, pacotes[i].dado);
  }
  
  //salvar dados em um arquivo
    FILE *q2csv = fopen("q2.csv", "w");
        if(q2csv) {
            printf("  (escrevendo dados da questao 2 em 'q2.csv')\n");
            
            // Imprimir dados em formato csv
            fprintf(q2csv, "ID,Dado\n");

            for(int i = 0; i < 20; i++){
                fprintf(q2csv, "%d,%c\n", pacotes[i].id, pacotes[i].dado);
            }
            fclose(q2csv);
        }
};
