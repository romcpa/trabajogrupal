#include <stdio.h>
#include "fabrica.h"

int main(void) {
    char prod[max_prod][max_nombre];
    int dem[max_prod];
    float tiempo[max_prod];
    float recursos[max_prod];
    int total = 0, opc;

    do {
        printf("\n=== FABRICA DE COMPONENTES ===\n");
        printf("1. Ingresar producto\n2. Mostrar productos\n3. Editar producto\n4. Eliminar producto\n5. Calcular optimizacion\n6. Salir\nOpcion: ");
        if (scanf("%d", &opc) != 1) { limpiarBuffer(); opc = 0; }

        switch (opc) {
            case 1: ingresarProducto(prod, dem, tiempo, recursos, &total); break;
            case 2: mostrarProductos(prod, dem, tiempo, recursos, total); break;
            case 3: editarProducto(prod, dem, tiempo, recursos, total); break;
            case 4: eliminarProducto(prod, dem, tiempo, recursos, &total); break;
            case 5: calcularOptimizacion(prod, dem, tiempo, recursos, total); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opc != 6);

    return 0;
}