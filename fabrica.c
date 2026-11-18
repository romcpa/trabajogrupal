#include <stdio.h>
#include "fabrica.h"

void limpiarBuffer(void) {
    while (getchar() != '\n');
}

int buscarProducto(char (*prod)[max_nombre], int total, const char *buscado) {
    for (int k = 0; k < total; k++) {
        int i = 0;
        while (*(*(prod + k) + i) == *(buscado + i) && *(*(prod + k) + i) != '\0') i++;
        if (*(*(prod + k) + i) == '\0' && *(buscado + i) == '\0') return k;
    }
    return -1;
}

void ingresarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int *total) {
    if (*total >= max_prod) {
        printf("\n[!] Capacidad maxima alcanzada (%d).\n", max_prod);
        return;
    }
    printf("\n--- NUEVO PRODUCTO ---\nNombre: ");
    scanf("%49s", *(prod + *total));
    
    if (buscarProducto(prod, *total, *(prod + *total)) != -1) {
        printf("[X] El producto ya existe.\n");
        return;
    }

    printf("Demanda: "); scanf("%d", dem + *total);
    printf("Tiempo por unidad (h): "); scanf("%f", tiempo + *total);
    printf("Recursos por unidad: "); scanf("%f", recursos + *total);
    limpiarBuffer();

    (*total)++;
    printf("[OK] Registrado con exito.\n");
}

void mostrarProductos(char (*prod)[max_nombre], const int *dem, const float *tiempo, const float *recursos, int total) {
    if (total == 0) {
        printf("\n[!] No hay productos registrados.\n");
        return;
    }
    printf("\n%-4s | %-15s | %-8s | %-10s | %-10s\n", "No.", "Producto", "Demanda", "Tiempo", "Recursos");
    printf("----------------------------------------------------------\n");
    for (int k = 0; k < total; k++) {
        printf("%-4d | %-15s | %-8d | %-10.2f | %-10.2f\n", 
            k + 1, *(prod + k), *(dem + k), *(tiempo + k), *(recursos + k));
    }
}

void editarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int total) {
    if (total == 0) { printf("\n[!] No hay productos.\n"); return; }
    
    char buscado[max_nombre];
    printf("\nNombre del producto a editar: ");
    scanf("%49s", buscado);
    
    int idx = buscarProducto(prod, total, buscado);
    if (idx == -1) { printf("[X] No encontrado.\n"); return; }

    printf("Nueva demanda: "); scanf("%d", dem + idx);
    printf("Nuevo tiempo unitario: "); scanf("%f", tiempo + idx);
    printf("Nuevos recursos unitarios: "); scanf("%f", recursos + idx);
    limpiarBuffer();
    printf("[OK] Actualizado.\n");
}

void eliminarProducto(char (*prod)[max_nombre], int *dem, float *tiempo, float *recursos, int *total) {
    if (*total == 0) { printf("\n[!] No hay productos.\n"); return; }

    char buscado[max_nombre];
    printf("\nNombre del producto a eliminar: ");
    scanf("%49s", buscado);

    int idx = buscarProducto(prod, *total, buscado);
    if (idx == -1) { printf("[X] No encontrado.\n"); return; }

    for (int k = idx; k < *total - 1; k++) {
        int i = 0;
        while ((*(*(prod + k) + i) = *(*(prod + k + 1) + i)) != '\0') i++;
        *(dem + k) = *(dem + k + 1);
        *(tiempo + k) = *(tiempo + k + 1);
        *(recursos + k) = *(recursos + k + 1);
    }
    (*total)--;
    printf("[OK] Eliminado.\n");
}

void calcularOptimizacion(char (*prod)[max_nombre], const int *dem, const float *tiempo, const float *recursos, int total) {
    if (total == 0) { printf("\n[!] Ingrese productos primero.\n"); return; }

    float tDisp, recDisp;
    printf("\nTiempo maximo disponible (h): "); scanf("%f", &tDisp);
    printf("Recursos maximos disponibles: "); scanf("%f", &recDisp);

    float tTot = 0, recTot = 0;
    for (int k = 0; k < total; k++) {
        tTot += (*(dem + k)) * (*(tiempo + k));
        recTot += (*(dem + k)) * (*(recursos + k));
    }

    printf("\n--- RESULTADOS ---\n");
    printf("Tiempo requerido: %.2f / Disponible: %.2f\n", tTot, tDisp);
    printf("Recursos requeridos: %.2f / Disponible: %.2f\n", recTot, recDisp);

    if (tTot <= tDisp && recTot <= recDisp) {
        printf("[ESTADO] VIABLE (Cumple con la demanda).\n");
    } else {
        printf("[ESTADO] NO VIABLE (Faltan recursos o tiempo).\n");
    }
}