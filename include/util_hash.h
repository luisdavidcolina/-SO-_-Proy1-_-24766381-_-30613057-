#ifndef UTIL_HASH_H
#define UTIL_HASH_H
#include "util_archivos.h"
int calcular_md5(const char *nombre_archivo, char *valor_hash, char modo);

int MDFile(char* filename, char hashValue[33]);

void crear_hash_lista(lista_archivos_t* lista, char modo);

int compararhashes(char* a, char* b);
#endif // UTIL_HASH_H