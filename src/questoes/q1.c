void questao1(unsigned int seed) {
    No* raiz = NULL;
    int inseridos = 0;
    int valores[20];

    while (inseridos < 20){
        int novo = rand() % 100;
        int repetido = 0;
        for(int i = 0; i < inseridos; i++) {
            if (valores [i] == novo) {
                repetido = 1;
                break;
            }
        }
        if (!repetido) {
            valores[inseridos++] = novo;
            raiz = inserir(raiz, novo);
        }
    }

    printf("valores inseridos:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", valores[i]);
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

    return 0;
};
