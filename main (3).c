#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    struct Producto productos[5];
    struct venta ventas[5];
    int totalVentas = 0;
    int opc;
    do {
        menu();
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                ingresarproducto(productos);
                break;
            case 2:
                imprimirproductos(productos);
                break;
            case 3:
                venta(productos, ventas, &totalVentas);
                break;
            case 4:
                imprimirventa(ventas, totalVentas);
                break;
            case 5:
                
                buscarventa(ventas, totalVentas);
                break;
            case 6:
                productoMasVendido(productos, ventas, totalVentas);
                break;
            case 7:
                imprimirClientes(ventas, totalVentas,productos);
                break;
            case 8:
                printf("Saliendo del programa...\n");
                break; 
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opc != 8);

    return 0;
}