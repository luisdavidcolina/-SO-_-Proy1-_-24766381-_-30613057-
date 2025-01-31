#include "include/util_hilos.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void inicializar_hilos(int num_hilos, const char *directorio_inicio, char modo) {
    pthread_t hilos[num_hilos];
    parametros_hilo_t parametros[num_hilos];

    for (int i = 0; i < num_hilos; i++) {
        parametros[i].directorio_inicio = directorio_inicio;
        parametros[i].modo = modo;
        if (pthread_create(&hilos[i], NULL, procesar_archivos, &parametros[i]) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }
}

void *procesar_archivos(void *arg) {
    parametros_hilo_t *parametros = (parametros_hilo_t *)arg;
    // Implementación del procesamiento de archivos
    return NULL;
}