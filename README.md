# Estrutura

O diretório do projeto segue a seguinte estrutura.

```
out/                Pasta de saída dos executáveis gerados pelo GCC.
src/                Pasta contendo o código do trabalho.
.gitignore          Lista de arquivos removidos do envio para o GitHub.
Makefile            Instruções para build do arquivo, leia mais abaixo.
README.md           O arquivo que você está lendo agora.
```

Os códigos relevantes ao trabalho devem ser armazenados na pasta `src`, e os executáveis gerados pelo GCC irão para o `out`. Os conteúdos da pasta `out` são filtrados para **não serem enviados** ao GitHub pelo arquivo chamado `.gitignore`.

# Como buildar

Ao baixar o projeto no computador, abra um terminal na pasta do projeto e execute o comando `make`. Isso executará todos os comandos do `gcc` necessários para buildar os executáveis do trabalho, que estarão na pasta `out`.

# Questões

- **Questão I.** Implementar vetor com **1.000.000 inteiros** e medir o tempo de execução da **busca sequencial** e **busca ordenada** com 30 valores de busca diferentes cada.

- **Questão II.** Fazer o mesmo da questão I, porém utilizando também uma lista encadeada. <br>
  Deve-se selecionar 30 valores de busca diferentes, e depois utilizá-los em **ambos** os algorítmos de busca.

- **Questão III.** Implementar vetor com 100.000 inteiros e medir o tempo de execução do bubble sort, insertion sort, selection sort, quicksort e merge sort. <br>
  Escolha 10 vetores diferentes com valores aleatórios, executando cada algorítmo de ordenação nesses 10 vetores.

- **Questão IV.** Apresentar os tempos de execução, médias e desvio padrão das questões I, II e III em uma tabela.

- **Questão V.** Apresentar gráficos mostrando o tempo de execução médio variando o tamanho do vetor nas questões I, II e III.

# Tarefas e Sugestões

- [ ] Criar TAD para um vetor para as questões I, III e V. <br>    
    ```c
    // No "vetor.h" ou "vetor.c" ...
    vetor_criar_aleatorio(tamanho);             // ^
    vetor_criar_ordenado(tamanho);              // |
    vetor_liberar(vetor);                       // | Questão I
    vetor_imprimir(vetor, inicio, fim);         // |
    vetor_buscar_seq(vetor, valor);             // |
    vetor_buscar_bin(vetor, valor);             // v
    vetor_ordernar_bubble(vetor);               // ^
    vetor_ordernar_insertion(vetor);            // |
    vetor_ordernar_selection(vetor);            // | Questão III
    vetor_ordernar_quicksort(vetor);            // |
    vetor_ordernar_mergesort(vetor);            // v
    ```

- [ ] Criar TAD para uma lista encadeada (ou lista simplesmente encadeada, ou ainda **LSE**) para as questões II e V.
    ```c
    // No "lse.h" ou "lse.c" ...
    lse_criar(tamanho);                 // ^ 
    lse_criar_ordenado(tamanho);        // |
    lse_criar_com_vetor(vetor);         // |
    lse_liberar(lista);                 // | Questão II
    lse_imprimir(lista, inicio, fim);   // |
    lse_buscar_seq(lista, valor);       // |
    lse_buscar_bin(lista, valor);       // v
    lse_acessar(lista, indice);         // ^
    lse_inserir_inicio(lista, valor);   // | Utilitários (privados)
    lse_inserir_final(lista, valor);    // v    
    ```