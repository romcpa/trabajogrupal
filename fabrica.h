#ifndef fabrica_h
#define fabrica_h

#define max_prod 5
#define max_nombre 50

void limpiarBuffer(void);
int buscarProducto(char (*prod)[max_nombre], int total, const char *buscado);

void ingresarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int *total);
void mostrarProductos(char (*prod)[max_nombre], const int *dem, const float *tiempo, const float *recursos, int total);
void editarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int total);
void eliminarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int *total);
void calcularOptimizacion(char (*prod)[max_nombre], const int *dem, const float *tiempo, const float *recursos, int total);

#endif