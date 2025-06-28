//una empreesa de repuestos de vehiculos tiene problemas para gestionar sus ventas dado que no puede extrear estadisticas como productos vendidos,clientes, ventas por lo cual se ha contactado con un ingeniero en software para que le ayude y debe proboner un demo que le permita vender el proyecyo
struct Producto
{
    char nombre[50];
    int precio;
};
struct cliente
{
    char nombre[50];
    int cedula;

};
struct venta
{
    struct Producto producto;
    struct cliente cliente;
    int cantidad;
    int seleccion;
    float total;
};

void ingresarproducto(struct Producto productos[5]);
void imprimirproductos(struct Producto productos[5]);
void venta(struct Producto productos[5], struct venta ventas[5], int *totalVentas);
void guardarventas(struct venta ventas[5], int totalVentas);
void leercadena(char *cadena, int num);
void imprimirventa(struct venta ventas[5], int totalVentas);
void menu();
void buscarventa(struct venta ventas[5], int totalVentas);
void productoMasVendido(struct Producto productos[5], struct venta ventas[5], int totalVentas);
void imprimirClientes(struct venta ventas[5], int totalVentas,struct Producto productos[5]);
void calcularTotalYGanancia(struct venta ventas[5], int totalVentas, struct Producto productos[5]);
