#include <stdio.h>      /* Incluye funciones estandar como printf y scanf */
#include <conio.h>      /* Proporciona funciones como getch y clrscr para manejo de la consola */
#include <ctype.h>      /* Incluye funciones como tolower para manipulacion de caracteres */
#include <stdlib.h>     /* Libreria estandar para funciones generales como system() */
#include <string.h>     /* Proporciona funciones para manipulacion de cadenas como strcmp */

#define SIZE_MAX 60     
#define PRO 20

typedef struct {
    char nombre[PRO];         /* Nombre del producto */
    float precio;             /* Precio del producto */
    int cantidad;             /* Cantidad del producto */
    char codigo[PRO];         /* Codigo del producto */
    char descripcion[PRO];    /* Descripcion del producto */
} productos;

/* Variables globales */
productos inventario[PRO];  /* Array global que almacena los productos */
int contador = 0;            /* Contador global para la cantidad de productos */

/* Variables globales para el usuario y el PIN */
int PIN = 1234;          
char USER[] = "hashell"; 

/* Declaracion de funciones */
void agregar_producto(productos *producto);
void buscar_producto(productos *producto);
void limpiar_buffer(void);
void credenciales(void);      
void menu_principal(void);     
void menu_inventario(void);    
void lowercase(char minuschar[]); 

void main() 
{
    credenciales();    
    menu_principal();  
}

/* Funcion que convierte una cadena a minusculas */
void lowercase(char minuschar[]) 
{ 
    int i = 0;
    for (i = 0; i < strlen(minuschar); i++) 
    {
        minuschar[i] = tolower(minuschar[i]); 
    }
}

/* Funcion que limpia el buffer de entrada */
void limpiar_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
}

/* Funcion para validar credenciales */
void credenciales(void)
{
    int contra; 
    char usuario[SIZE_MAX]; 
    int acceso_concedido = 0; 

    while (!acceso_concedido) 
    {
        clrscr(); 
        printf("---Credenciales---\n\n");

        printf("username: \n");
        gets(usuario);  /* Usa gets para obtener el usuario */

        printf("password: \n");
        scanf(" %i", &contra); 
        limpiar_buffer();  /* Limpia el buffer para evitar problemas con gets y scanf */

        lowercase(usuario); 

        /* Validacion de credenciales */
        if (strcmp(usuario, USER) != 0 && contra != PIN) 
        {
            clrscr();
            printf("TODO MAL, pruebe de nuevo:\n");
            getch();
        } 
        else if (contra != PIN) 
        {
            clrscr();
            printf("PIN incorrecto, pruebe de nuevo:\n");
            getch();
        } 
        else if (strcmp(usuario, USER) != 0) 
        {
            clrscr();
            printf("Usuario incorrecto, pruebe de nuevo:\n");
            getch();
        } 
        else 
        {
            clrscr();
            printf("Acceso concedido\n");
            getch();
            acceso_concedido = 1; 
        }
    }
}

/* Menu principal */
void menu_principal(void)
{
    char opc; 

    clrscr(); 
    printf("--- 1. Inventario:\n");
    printf("--- 2. Ventas: \n");
    printf("--- 3. Salir: \n");

    scanf(" %c", &opc); 
    limpiar_buffer(); 

    switch (opc)
    {
        case '1': 
            menu_inventario(); 
            getch();
            break;
        
        case '2': 
            printf("2.");
            getch();
            break;
        
        case '3': 
            clrscr();
            credenciales();
            break;
        
        default: 
            clrscr();
            menu_principal();
            break;
    }
}

/* Menu de inventario */
void menu_inventario(void)
{
    char opc_inventario;

    clrscr(); 
    printf("--- 1. Agregar producto:\n");
    printf("--- 2. Buscar producto: \n");
    printf("--- 3. Actualizar producto: \n");
    printf("--- 4. Eliminar producto:\n");
    printf("--- 5. Volver al menu principal: \n");
    printf("--- 6. Salir: \n");

    scanf(" %c", &opc_inventario); 
    limpiar_buffer(); 

    switch (opc_inventario)
    {
        case '1':
            agregar_producto(inventario);
            getch();
            break;

        case '2':
			buscar_producto(inventario);
            getch();
            break;

        case '3':
            printf("3.");
            getch();
            break;

        case '4':
            printf("4.");
            getch();
            break;

        case '5':
            printf("5.");
            getch();
            break;

        case '6':
            clrscr();
            break;

        default:
            clrscr();
            menu_inventario();
            break;
    }
}

/* Funcion para agregar productos */
void agregar_producto(productos *producto)
{
    char buffer[100];  /* Para almacenar temporalmente los valores ingresados */
    int terminar = 0, i=0;
    clrscr();

    /* Comenzar a agregar productos mientras haya espacio */
    while (contador < PRO)
    {
        /* Obtener nombre del producto */
        printf("Nombre del producto: ");
        fgets(producto[contador].nombre, PRO, stdin);
        producto[contador].nombre[strcspn(producto[contador].nombre, "\n")] = 0;

        /* Obtener codigo del producto */
        printf("Codigo del producto: ");
        fgets(producto[contador].codigo, PRO, stdin);
        producto[contador].codigo[strcspn(producto[contador].codigo, "\n")] = 0;

        /* Leer cantidad del producto */
        printf("Cantidad del producto: ");
        fgets(buffer, sizeof(buffer), stdin);
        producto[contador].cantidad = atoi(buffer);  /* Convertir a entero */

        /* Leer precio del producto */
        printf("Precio del producto: ");
        fgets(buffer, sizeof(buffer), stdin);
        producto[contador].precio = atof(buffer);  /* Convertir a flotante */

        /* Obtener descripcion del producto */
        printf("Descripcion del producto: ");
        fgets(producto[contador].descripcion, PRO, stdin);
        producto[contador].descripcion[strcspn(producto[contador].descripcion, "\n")] = 0;

        getch();
        clrscr();

        /* Imprimir detalles del producto ingresado */
        printf("Producto N %d:  Nombre: ", contador + 1);

        for(i = 0; i < PRO; i++)
        {
            printf("%c",producto[contador].nombre[i]);
        }
        printf("\n");

        printf("Producto N %d:  Codigo: ", contador + 1);

        for(i = 0; i < PRO; i++)
        {
            printf("%c",producto[contador].codigo[i]);
        }
        printf("\n");
        printf("Producto N %d:  Cantidad: %i\n", contador + 1, producto[contador].cantidad);
        printf("Producto N %d:  Precio: %.2f\n", contador + 1, producto[contador].precio);

		printf("Producto N %d:  Descripcion:", contador + 1);

        for(i = 0; i < PRO; i++)
        {
            printf("%c",producto[contador].descripcion[i]);
        }
        printf("\n");

        /* Preguntar si desea agregar otro producto */
        printf("Desea agregar otro producto [1 Para continuar / 2 Para volver al Inventario]: ");
        fgets(buffer, sizeof(buffer), stdin);
		terminar = atoi(buffer);  /* Convertir a entero */

        /* Si el usuario quiere continuar, incrementar el contador y llamar a la funcion nuevamente */
        if (terminar == 1)
        {
            contador++;  /* Incrementar el contador */
            clrscr();    /* Limpiar la pantalla para el siguiente producto */
        }
        else if (terminar == 2)
        {
            /* Volver al menu de inventario */
            menu_inventario();
            break;  /* Salir del bucle */
        }
    }

    /* Si el contador ha alcanzado el maximo de productos */
    if (contador >= PRO) {
        printf("Limite de productos alcanzado.\n");
        getch();
        menu_inventario();
    }
}

void buscar_producto(productos *producto)
{
    char buscar[SIZE_MAX];
    char termi[SIZE_MAX];
    int i, j, encontrado = 0;
    int terminar = 0;
    clrscr();

    printf("--Busqueda: [CODIGO] O [NOMBRE]: ");
    gets(buscar);
    limpiar_buffer();
    

    while (!terminar)
    {
        clrscr();
        printf("--Busqueda: [CODIGO] O [NOMBRE]: ");
        gets(buscar);
        limpiar_buffer();

        encontrado = 0;  /* Reiniciar la variable de coincidencia */

        for (i = 0; i < contador; i++)
        {
            /* Comparar con el nombre del producto */
            encontrado = 1;  
                if (strcmp(buscar, producto[i].nombre) == 1)
                {
                    encontrado = 0;  
                    break;
                }

            if (encontrado)
            {
                printf("-- PRODUCTO ENCONTRADO (por nombre) --\n");
                printf("Nombre: ");
                for (j = 0; j < PRO; j++) 
                {   
                    printf("%s", producto[i].nombre[j]);
                    printf("\n");
                    break;
                }
            }

            /* Comparar con el codigo del producto */
            encontrado = 1;             
                if (strcmp(buscar, producto[i].codigo) == 1)
                {
                    encontrado = 0;
                    break;
                }
            

            if (encontrado)
            {
                printf("-- CODIGO ENCONTRADO --\n");
                printf("Codigo: ");
                for (j = 0; j < PRO; j++)
                {
                    printf("%c", producto[i].codigo[j]);
                    printf("\n");
                    break;
                }
            }
        }

        if (!encontrado)
        {
            printf("-- No se ha encontrado nada --\n");
        }

        printf("Desea buscar otro producto [1 Para continuar / 2 Para volver al Inventario]: ");
        fgets(termi, sizeof(termi), stdin);  /* Reutilizando 'buscar' para la entrada */
        limpiar_buffer();
        terminar = atoi(termi);  /* Convertir a entero */

        if(terminar == 1)
        {
            terminar = 0;
        }

        
        /* Si el usuario selecciona volver al inventario */
        if (terminar == 2)
        {
            menu_inventario();
        }
    }
}
