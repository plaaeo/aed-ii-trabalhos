#pragma once
#include <stdbool.h>
#include "grafo.h"

/// Retorna verdadeiro se o grafo contiver um ciclo de tamanho ≥ 3
bool grafo_tem_ciclo(const grafo_t *grafo);
