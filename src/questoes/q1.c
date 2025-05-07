void questao1(unsigned int seed) {
    No* raiz = NULL;
    valores = srand(NULL);
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }
    printf("Pré-fixado: ");
    pre_ordem(raiz);
    printf("\n");

    printf("Central: ");
    em_ordem(raiz);
    printf("\n");

    printf("Pós-fixado: ");
    pos_ordem(raiz);
    printf("\n");
  
};
