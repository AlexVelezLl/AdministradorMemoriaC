#include <stdio.h>
#include <memadmin.h>
#include <stdlib.h>

void mostrar_opciones();
void realizar_opcion(int opc);
void aumentar_tam_arreglo();

//Funciones del menu
void reservar_bloque_nuevo();
void reservar_bloque_cero();
void liberar_bloque();
void reasignar_bloque();
void actualizar_direcciones();
void agrandar_arreglo();
void mostrar_estado_nodos();

void **punteros;
int TAM = 100;
int efectivo = 0;
int main()
{
	punteros = malloc(TAM * sizeof(void *));
	int opcion = 0;
	printf("╔═══════════════════════════════════════════╗\n");
	printf("║     PRUEBAS ADMINISTRADOR DE MEMORIA      ║\n");
	printf("╚═══════════════════════════════════════════╝\n\n\n");
	int opc;
	do
	{
		mostrar_opciones();
		scanf("%d", &opc);
		realizar_opcion(opc);
		printf("Operacion Terminada!\n\n");
	} while (opc != 9);
	printf("Saliendo...\n");
	printf("Destruyendo administrador de memoria.\n");
	destruir_admin();
	free(punteros);
}

void mostrar_opciones()
{
	printf("══════════════Opciones══════════════\n");
	printf("1.- Reservar bloque de memoria.\n");
	printf("2.- Reservar bloque de memoria inicializado en cero.\n");
	printf("3.- Liberar bloque de memoria.\n");
	printf("4.- Reasignar bloque de memoria.\n");
	printf("5.- Desfragmentar memoria.\n");
	printf("6.- Actualizar direcciones de memoria\n");
	printf("7.- Mostrar estado del administrador de memoria\n");
	printf("8.- Mostrar bloques usados \n");
	printf("9.- Salir\n");
}

void realizar_opcion(int opc)
{
	switch (opc)
	{
	case 1:
		reservar_bloque_nuevo();
		break;
	case 2:
		reservar_bloque_cero();
		break;
	case 3:
		liberar_bloque();
		break;
	case 4:
		reasignar_bloque();
		break;
	case 5:
		desfragmentar();
		break;
	case 6:
		actualizar_direcciones();
		break;
	case 7:
		mostrar_estado();
		break;
	case 8:
		mostrar_estado_nodos();
		break;
	case 9:
		printf("Saliendo...\n");
		break;
	default:
		printf("No ha ingresado una opcion correcta, por favor ingrese una opcion correcta\n");
		break;
	}
}

void reservar_bloque_nuevo()
{
	int n_bloques;
	printf("Cuantos bloques desea reservar: ");
	scanf("%d", &n_bloques);
	int tam;
	printf("Tamaño de los bloques que desea reservar: ");
	scanf("%d", &tam);
	for (int i = 0; i < n_bloques; i++)
	{
		*(punteros + efectivo + i) = memasign(tam);
	}
}

void reservar_bloque_cero()
{
	int n_bloques;
	printf("Cuantos bloques desea reservar: ");
	scanf("%d", &n_bloques);
	int tam;
	printf("Tamaño de los bloques que desea reservar: ");
	scanf("%d", &tam);
	for (int i = 0; i < n_bloques; i++)
	{
		*(punteros + efectivo + i) = casign(tam);
	}
}

void liberar_bloque()
{
	printf("Escriba el id del bloque que desea liberar: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	liberar(*(punteros + id_bloque));
}

void reasignar_bloque()
{
	printf("Escriba el id del bloque que desea reasignar: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	printf("Escriba el nuevo tamaño que le desea asignar: ");
	int new_tam;
	scanf("%d", &new_tam);
	reasignar(*(punteros + id_bloque), new_tam);
}

void actualizar_direcciones()
{
}

void mostrar_estado_nodos() {}

void aumentar_tam_arreglo()
{
	punteros = realloc(punteros, TAM * 2);
	TAM *= 2;
}