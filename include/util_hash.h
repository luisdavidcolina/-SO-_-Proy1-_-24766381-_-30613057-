#ifndef UTIL_HASH_H
#define UTIL_HASH_H

int calcular_md5(const char *nombre_archivo, char *valor_hash, char modo);

int MDFile(char* filename, char hashValue[33]);
#endif // UTIL_HASH_H