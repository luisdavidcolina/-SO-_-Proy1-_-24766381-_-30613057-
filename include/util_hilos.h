#ifndef UTIL_HILOS_H
#define UTIL_HILOS_H

typedef struct {
    const char *directorio_inicio;
    char modo;
} parametros_hilo_t;

void inicializar_hilos(int num_hilos, const char *directorio_inicio, char modo);
void *procesar_archivos(void *arg);

#endif // UTIL_HILOS_H