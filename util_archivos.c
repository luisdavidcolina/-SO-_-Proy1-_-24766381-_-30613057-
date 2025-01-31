#include "include/util_archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listar_archivos(const char *nombre_directorio, lista_archivos_t *lista_archivos) {
    DIR *dir;
    struct dirent *entrada;

    if ((dir = opendir(nombre_directorio)) == NULL) {
        perror("No se puede abrir el directorio");
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            // Agregar archivo a la lista
        }
    }

    closedir(dir);
}