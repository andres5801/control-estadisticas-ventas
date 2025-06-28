#include <stdio.h>
#include <string.h>
#include "funciones.h"

void ingresarproducto(struct Producto productos[5])
{
    FILE *archivoVentas = fopen("ventas.dat", "wb");
    if (archivoVentas == NULL)
    {
        printf("Error al reiniciar el archivo de ventas.\n");
        return;
    }
    FILE *archivoClientes = fopen("clientes.dat", "wb");
    if (archivoClientes == NULL) {
        printf("Error al reiniciar el archivo de clientes.\n");
        return;
    }
    fclose(archivoClientes);

    fclose(archivoVentas);
    strcpy(productos[0].nombre, "Aceite");
    productos[0].precio = 10;
    strcpy(productos[1].nombre, "Filtro de aire");
    productos[1].precio = 15;
    strcpy(productos[2].nombre, "Bujias");
    productos[2].precio = 5;
    strcpy(productos[3].nombre, "Pastillas de freno");
    productos[3].precio = 20;
    strcpy(productos[4].nombre, "Neumaticos");
    productos[4].precio = 50;
    guardarproductos(productos);
}
void guardarproductos(struct Producto productos[5])
{

    FILE *archivo = fopen("productos.dat", "wb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para guardar los productos.\n");
        return;
    }

    fwrite(productos, sizeof(struct Producto), 5, archivo);

    fclose(archivo);
}
void menu()
{
    printf("Menu de opciones:\n");
    printf("1. Ingresar productos\n");
    printf("2. Ver productos\n");
    printf("3.realizar venta\n");
    printf("4.ver ventas totales\n");
    printf("5.buscar venta\n");
    printf("6. Producto mas vendido\n");
    printf("7. Imprimir clientes registrados\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
}

void imprimirproductos(struct Producto productos[5])
{
    FILE *archivo = fopen("productos.dat", "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para leer los productos.\n");
        return;
    }

    fread(productos, sizeof(struct Producto), 5, archivo);

    fclose(archivo);

    printf("Productos disponibles:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s - Precio: %d\n", productos[i].nombre, productos[i].precio);
    }
}
void venta(struct Producto productos[5], struct venta ventas[5], int *totalVentas)
{
    struct venta nuevaVenta;
    int op;
    printf("Ingrese el nombre del cliente: ");
    leercadena(nuevaVenta.cliente.nombre, 50);

    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &nuevaVenta.cliente.cedula);
    printf("seleccione el producto a vender:\n");
    FILE *archivo = fopen("productos.dat", "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }
    if (fread(productos, sizeof(struct Producto), 5, archivo) != 5)
    {
        printf("Error al leer los productos del archivo.\n");
        fclose(archivo);
        return;
    }
    fclose(archivo);
    for (int i = 0; i < 5; i++)
    {
        printf("%d. %s - Precio: %d\n", i + 1, productos[i].nombre, productos[i].precio);
    }
    do
    {
        printf("seleccione el producto a vender:\n");
        scanf("%d", &nuevaVenta.seleccion);
        switch (nuevaVenta.seleccion)
        {

        case 1:
            printf("Producto seleccionado: %s\n", productos[0].nombre);
            nuevaVenta.producto = productos[0];
            printf("Ingrese la cantidad: ");
            scanf("%d", &nuevaVenta.cantidad);
            nuevaVenta.total = nuevaVenta.cantidad * productos[0].precio;

            break;
        case 2:
            printf("Producto seleccionado: %s\n", productos[1].nombre);
            nuevaVenta.producto = productos[1];
            printf("Ingrese la cantidad: ");
            scanf("%d", &nuevaVenta.cantidad);
            nuevaVenta.total = nuevaVenta.cantidad * productos[1].precio;

            break;
        case 3:
            printf("Producto seleccionado: %s\n", productos[2].nombre);
            nuevaVenta.producto = productos[2];
            printf("Ingrese la cantidad: ");
            scanf("%d", &nuevaVenta.cantidad);
            nuevaVenta.total = nuevaVenta.cantidad * productos[2].precio;

            break;
        case 4:
            printf("Producto seleccionado: %s\n", productos[3].nombre);
            nuevaVenta.producto = productos[3];
            printf("Ingrese la cantidad: ");
            scanf("%d", &nuevaVenta.cantidad);
            nuevaVenta.total = nuevaVenta.cantidad * productos[3].precio;

            break;
        case 5:
            printf("Producto seleccionado: %s\n", productos[4].nombre);
            nuevaVenta.producto = productos[4];
            printf("Ingrese la cantidad: ");
            scanf("%d", &nuevaVenta.cantidad);
            nuevaVenta.total = nuevaVenta.cantidad * productos[4].precio;

            break;
        default:
            break;
        }
        printf("Desea realizar otra venta? (1. Si, 2. No): ");
        scanf("%d", &op);

    } while (op == 1);

    ventas[*totalVentas] = nuevaVenta;
    (*totalVentas)++;

    printf("Venta realizada con exito. Total: %.2f\n", nuevaVenta.total);
    guardarventas(ventas, *totalVentas);
}

void guardarventas(struct venta ventas[5], int totalVentas)
{
    if (totalVentas <= 0)
    {
        printf("No hay ventas para guardar.\n");
        return;
    }

    FILE *archivo = fopen("ventas.dat", "wb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para guardar las ventas");
        return;
    }

    for (int i = 0; i < totalVentas; i++)
    {
        fwrite(&ventas[i], sizeof(struct venta), 1, archivo);
    }

    fclose(archivo);
    printf("Ventas guardadas correctamente.\n");
}
void leercadena(char *cadena, int num)
{
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0'; // Eliminar el salto de línea al final
}

void buscarventa(struct venta ventas[5], int totalVentas)
{
    int cedula;
    printf("Ingrese la cedula del cliente a buscar: ");
    scanf("%d", &cedula);

    int encontrado = 0;
    for (int i = 0; i < totalVentas; i++)
    {
        if (ventas[i].cliente.cedula == cedula)
        {
            printf("Venta encontrada:\n");
            printf("Cliente: %s, Cedula: %d, Producto: %s, Cantidad: %d, Total: %.2f\n",
                   ventas[i].cliente.nombre,
                   ventas[i].cliente.cedula,
                   ventas[i].producto.nombre,
                   ventas[i].cantidad,
                   ventas[i].total);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("No se encontraron ventas para el cliente con cedula %d.\n", cedula);
    }
}
void productoMasVendido(struct Producto productos[5], struct venta ventas[5], int totalVentas)
{
    int cantidades[5] = {0}; // Arreglo para acumular las cantidades vendidas de cada producto

    // Recorrer las ventas y acumular las cantidades por producto
    for (int i = 0; i < totalVentas; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (strcmp(ventas[i].producto.nombre, productos[j].nombre) == 0)
            {
                cantidades[j] += ventas[i].cantidad;
                break;
            }
        }
    }

    // Depuración: Imprimir las cantidades acumuladas
    printf("Cantidades acumuladas por producto:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s: %d\n", productos[i].nombre, cantidades[i]);
    }

    // Determinar el producto más vendido
    int maxCantidad = 0;
    int indiceMax = -1;
    for (int i = 0; i < 5; i++)
    {
        if (cantidades[i] > maxCantidad)
        {
            maxCantidad = cantidades[i];
            indiceMax = i;
        }
    }

    // Imprimir el resultado
    if (indiceMax != -1)
    {
        printf("El producto más vendido es: %s\n", productos[indiceMax].nombre);
        printf("Cantidad total vendida: %d\n", maxCantidad);
    }
    else
    {
        printf("No se han realizado ventas.\n");
    }
}

void imprimirClientes(struct venta ventas[5], int totalVentas, struct Producto productos[5])
{
    if (totalVentas <= 0)
    {
        printf("No hay clientes registrados.\n");
        return;
    }
    FILE *archivo = fopen("clientes.dat", "wb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para guardar los clientes.\n");
        return;
    }

    printf("Clientes registrados y sus ventas:\n");
    for (int i = 0; i < totalVentas; i++)
    {
        printf("Cliente: %s, Cedula: %d, Total de la venta: %.2f\n",
               ventas[i].cliente.nombre,
               ventas[i].cliente.cedula,
               ventas[i].total);
        fwrite(&ventas[i].cliente, sizeof(struct cliente), 1, archivo);

        fclose(archivo);
        printf("Clientes guardados correctamente en clientes.dat.\n");
    }
    calcularTotalYGanancia(ventas, totalVentas, productos);
}

void imprimirventa(struct venta ventas[5], int totalVentas)
{
    FILE *archivo = fopen("ventas.dat", "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }

    int ventasLeidas = fread(ventas, sizeof(struct venta), totalVentas, archivo);
    fclose(archivo);

    if (ventasLeidas <= 0)
    {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("Ventas realizadas:\n");
    for (int i = 0; i < ventasLeidas; i++)
    {
        printf("Cliente: %s, Cedula: %d, Producto: %s, Cantidad: %d, Total: %.2f\n",
               ventas[i].cliente.nombre,
               ventas[i].cliente.cedula,
               ventas[i].producto.nombre,
               ventas[i].cantidad,
               ventas[i].total);
    }
}
void calcularTotalYGanancia(struct venta ventas[5], int totalVentas, struct Producto productos[5])
{
    if (totalVentas <= 0)
    {
        printf("No hay ventas registradas.\n");
        return;
    }

    float totalVentasRealizadas = 0; // Acumular el total de todas las ventas
    float costoTotal = 0;            // Acumular el costo total de los productos vendidos

    // Recorrer las ventas para calcular el total y el costo
    for (int i = 0; i < totalVentas; i++)
    {
        totalVentasRealizadas += ventas[i].total;

        // Calcular el costo total basado en los productos vendidos
        for (int j = 0; j < 5; j++)
        {
            if (strcmp(ventas[i].producto.nombre, productos[j].nombre) == 0)
            {
                costoTotal += ventas[i].cantidad * productos[j].precio * 0.6; // Ejemplo: 60% del precio como costo
                break;
            }
        }
    }

    // Calcular el margen de ganancia
    float ganancia = totalVentasRealizadas - costoTotal;
    float porcentajeGanancia = (ganancia / totalVentasRealizadas) * 100;

    // Imprimir los resultados
    printf("Total de ventas realizadas: %.2f\n", totalVentasRealizadas);
    printf("Costo total de los productos vendidos: %.2f\n", costoTotal);
    printf("Ganancia total: %.2f\n", ganancia);
    printf("Margen de ganancia: %.2f%%\n", porcentajeGanancia);
}