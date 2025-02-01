#include <stdlib.h>

#ifndef UTIL_ARCHIVOS_H
#define UTIL_ARCHIVOS_H

typedef struct {
    char* valor;
    void* siguente;
    void* anterior;
    char* hashID;
} Nodo;

typedef struct {
    // Definir estructura para la lista de archivos
    Nodo* cabecera;
    Nodo*  cola;
} lista_archivos_t;



void agregar(lista_archivos_t* lista, char *valor);
int eliminar(lista_archivos_t *lista, Nodo *nodo);
char *obtenerNombreArchivo(const char *ruta);
void listar_archivos(const char *nombre_directorio, lista_archivos_t *lista_archivos);

#endif // UTIL_ARCHIVOS_H

