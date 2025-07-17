#include "util.h"

#include <stdio.h>

/// Para a execução do código até que receba uma entrada.
/// Limpa a tela ao receber a entrada.
void aguardar_entrada() {
    printf("\nPressione qualquer caractére para continuar a execução...\n");
    getchar();
    printf("\033[2J\033[H");
};
