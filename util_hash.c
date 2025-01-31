#include "include/util_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcular_md5(const char *nombre_archivo, char *valor_hash, char modo) {
    if (modo == 'e') {
        // Usar modo ejecutable
        char comando[256];
        snprintf(comando, sizeof(comando), "./md5-app/md5 %s", nombre_archivo);
        FILE *fp = popen(comando, "r");
        if (fp == NULL) {
            perror("Error al ejecutar el comando md5");
            return 0;
        }
        fgets(valor_hash, 33, fp);
        pclose(fp);
    } else if (modo == 'l') {
        // Usar modo biblioteca
        if (MDFile((char *)nombre_archivo, valor_hash) == 0) {
            fprintf(stderr, "Error al calcular el hash MD5\n");
            return 0;
        }
    }
    return 1;
}