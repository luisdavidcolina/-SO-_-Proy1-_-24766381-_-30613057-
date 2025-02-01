#include "include/util_hash.h"
#include "include/util_archivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compararhashes(char* a, char* b){
    if(strcmp(a,b) == 0){
        return 1;
    }
    
    return 0;
}

//Codigo para la aplicacion de MD5 en distintas modalidades para su uso en el proceso con los archivos


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

void crear_hash_lista(lista_archivos_t* lista, char modo){
    if(lista == NULL){
        return;
    }

    Nodo* cabecera = lista->cabecera;
    while(cabecera != NULL){
        char hash[33];
        calcular_md5(cabecera->valor, hash, modo);
        cabecera->hashID = (char*)malloc(strlen(hash) + 1);
        strcpy(cabecera->hashID, hash);
        cabecera = cabecera->siguente;
    }
    
}