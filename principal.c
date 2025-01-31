#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "include/util_archivos.h"
#include "include/util_hash.h"
#include "include/util_hilos.h"

int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Uso: %s -t <numero de hilos> -d <directorio de inicio> -m <e | l>\n", argv[0]);
        return 1;
    }

    int num_hilos = atoi(argv[2]);
    char *directorio_inicio = argv[4];
    char modo = argv[6][0];

    if (modo != 'e' && modo != 'l') {
        fprintf(stderr, "Modo inválido. Use 'e' para modo ejecutable o 'l' para modo biblioteca.\n");
        return 1;
    }

    // Inicializar y comenzar los hilos
    inicializar_hilos(num_hilos, directorio_inicio, modo);

    return 0;
}