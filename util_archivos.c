#include "include/util_archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

//Manipulacion de archivospara duplicados


void agregar(lista_archivos_t* lista, char *valor)
{
    if (lista == NULL)
        return;

    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->siguente = NULL;
    nuevoNodo->anterior = NULL;

    // Verifica si no hay ningun elemento
    if (lista->cabecera == NULL)
    {
        // Inserta el nuevo elemento
        lista->cabecera = nuevoNodo;
        lista->cola = nuevoNodo;
        return;
    }

    // Inserta el nuevo elemento al final
    lista->cola->siguente = nuevoNodo;
    nuevoNodo->anterior = lista->cola;
    lista->cola = nuevoNodo;
    return;
};

int eliminar(lista_archivos_t *lista, Nodo *nodo)
{
    if (lista == NULL || nodo == NULL)
        return 0;

    if (nodo == lista->cabecera)
    {
        lista->cabecera = nodo->siguente;
        if (lista->cabecera != NULL)
        {
            lista->cabecera->anterior = NULL;
        }
        else
        {
            lista->cola = NULL; // Si la lista queda vacía
        }

       
        return 1;
    }

    if (nodo == lista->cola)
    {
        lista->cola = nodo->anterior;
        lista->cola->siguente = NULL;
     
        return 1;
    }
    Nodo* temp= (Nodo*)nodo->anterior;
    temp->siguente = nodo->siguente;
    temp = (Nodo*)nodo->siguente;
    temp->anterior = nodo->anterior;


    return 1;
};


void listar_archivos(const char *nombre_directorio, lista_archivos_t *lista_archivos) {
    DIR *dir;
    struct dirent *entrada;

    if ((dir = opendir(nombre_directorio)) == NULL) {
        perror("No se puede abrir el directorio");
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0)
        {
            char d[1024];
            snprintf(d, sizeof(d), "%s/%s", nombre_directorio, entrada->d_name);

            struct stat info;
            if (lstat(d, &info) == 0)
            {
                char *directorio = (char *)malloc(strlen(d) + 1);
                strcpy(directorio, d);

                if (S_ISDIR(info.st_mode))
                {
                  
                    listar_archivos(directorio, lista_archivos);
                }

                if ( !S_ISDIR(info.st_mode) && !S_ISLNK(info.st_mode) && info.st_size != 0)
                {
                    agregar(lista_archivos, directorio);
                }
                
            }
        }
    }

    closedir(dir);
}

char *obtenerNombreArchivo(const char *ruta) {
    // Busca la última aparición de '/'
    char *nombre = strrchr(ruta, '/');
    // Si se encuentra, devuelve el puntero al siguiente carácter
    return (nombre != NULL) ? (nombre + 1) : (char *)ruta; // Si no hay '/', devuelve la ruta completa
}