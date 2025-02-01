#include "include/util_hilos.h"
#include "include/util_hash.h"
#include "include/util_archivos.h"
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

char *salida;
sem_t paraVisitar;
sem_t visitados;
int duplicados = 0; // Contador de duplicados

void inicializar_hilos(int num_hilos, const char *directorio_inicio, char modo) {
    pthread_t* hilos = (pthread_t*)malloc(sizeof(pthread_t)*num_hilos);

    lista_archivos_t* archivos = (lista_archivos_t*)malloc(sizeof(lista_archivos_t));
    archivos->cabecera = NULL;
    archivos->cola = NULL;
    listar_archivos(directorio_inicio, archivos);
    
    crear_hash_lista(archivos, modo);
    sem_init(&paraVisitar, 0, 1);
    sem_init(&visitados, 0, 1);

    salida = malloc(2044 * sizeof(char)); // Buffer para la salida
    if (salida == NULL) {
        perror("Error al asignar memoria");
        return;
    }

    salida[0] = '\0'; // Inicializa el buffer

    for (int i = 0; i < num_hilos; i++) {
   
        if (pthread_create(&hilos[i], NULL, procesar_archivos, archivos) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir el número total de duplicados
    printf("Se han encontrado %d archivos duplicados.\n\n", duplicados);
    printf("%s", salida); // Imprimir la salida acumulada

    free(salida); // Liberar la memoria del buffer
}

void *procesar_archivos(void *arg) {
    lista_archivos_t *parametros = (lista_archivos_t *)arg; // Cmo aun no esta implementado causa problemas
    while(1){
         sem_wait(&paraVisitar);
        if (parametros->cabecera == NULL)
        {
            sem_post(&paraVisitar);
            break;
        }

        Nodo* actual = parametros->cabecera;
        
        parametros->cabecera = actual->siguente;
        if (parametros->cabecera != NULL){

            parametros->cabecera->anterior = NULL;
        }
        else{
            parametros->cola = NULL;
        }

    Nodo* comparador = actual->siguente;

    // Comparar el nodo actual con los siguientes
    while (comparador != NULL) {
        if (compararhashes(actual->hashID, comparador->hashID)) {
            // Formatear la salida y agregarla al buffer
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%s es duplicado de %s\n", obtenerNombreArchivo(comparador->valor), obtenerNombreArchivo(actual->valor));
            strcat(salida, buffer);
            duplicados++;
            Nodo* temp = comparador;
            comparador = comparador->siguente;
            eliminar(parametros, temp);
            continue;
        }
        comparador = comparador->siguente;
    }
    sem_post(&paraVisitar);
    }
    
    return NULL;
}