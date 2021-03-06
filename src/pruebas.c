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
void dar_contenido();
void mostrar_contenido();
void mostrar_superbloques();
void mostrar_estado_nodos();

void **punteros;
int *tamanos;
int TAMAN = 100;
int efectivo = 0;
int main()
{
	punteros = malloc(TAMAN * sizeof(void *));
	tamanos = malloc(TAMAN * sizeof(int));
	int opcion = 0;
	printf("╔═══════════════════════════════════════════╗\n");
	printf("║     PRUEBAS ADMINISTRADOR DE MEMORIA      ║\n");
	printf("╚═══════════════════════════════════════════╝\n\n\n");
	int opc;
	do
	{
		mostrar_opciones();
		printf("Escoja una opcion: ");
		scanf("%d", &opc);
		realizar_opcion(opc);
		printf("Operacion Terminada!\n\n");
	} while (opc != 12);
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
	printf("6.- Actualizar direcciones de memoria.\n");
	printf("7.- Asignar contenido.\n");
	printf("8.- Mostrar contenido.\n");
	printf("9.- Mostrar estado del administrador de memoria.\n");
	printf("10.- Mostrar estado de superbloques.\n");
	printf("11.- Mostrar bloques usados.\n");
	printf("12.- Salir\n");
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
		dar_contenido();
		break;

	case 8:
		mostrar_contenido();
		break;

	case 9:
		mostrar_estado();
		break;

	case 10:
		mostrar_superbloques();
		break;

	case 11:
		mostrar_estado_nodos();
		break;

	case 12:
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
		if (efectivo == TAMAN)
		{
			aumentar_tam_arreglo();
		}
		*(punteros + efectivo + i) = memasign(tam);
		*(tamanos + efectivo + i) = tam;
	}
	efectivo += n_bloques;
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
		if (efectivo == TAMAN)
		{
			aumentar_tam_arreglo();
		}
		*(punteros + efectivo + i) = casign(tam);
		*(tamanos + efectivo + i) = tam;
		efectivo++;
	}
}

void liberar_bloque()
{
	printf("Escriba el id del bloque que desea liberar: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	liberar(*(punteros + id_bloque));
	*(punteros + id_bloque) = NULL;
}

void reasignar_bloque()
{
	printf("Escriba el id del bloque que desea reasignar: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	printf("Escriba el nuevo tamaño que le desea asignar: ");
	int new_tam;
	scanf("%d", &new_tam);
	*(punteros + id_bloque) = reasignar(*(punteros + id_bloque), new_tam);
	*(tamanos + id_bloque) = new_tam;
}

void actualizar_direcciones()
{
	for (int i = 0; i < efectivo; i++)
	{
		if (*(punteros + i) != NULL)
		{
			*(punteros + i) = nueva_dir(*(punteros + i));
		}
	}
}

void mostrar_estado_nodos()
{

	for (int i = 0; i < efectivo; i++)
	{
		if (*(punteros + i) != NULL)
		{
			printf("****Id del nodo: %d\n", i);
			mostrar_nodo(*(punteros + i));
		}
	}
}

void aumentar_tam_arreglo()
{
	punteros = realloc(punteros, TAMAN * 2);
	TAMAN *= 2;
}

void llenar_bytes(void *ptr, int tam)
{
	int MAX = 256;
	int num = 0;
	unsigned char *punt = (unsigned char *)ptr;
	for (int i = 0; i < tam; i++)
	{
		*(punt + i) = (char)num;
		num = (num + 1) % MAX;
	}
}

void dar_contenido()
{
	printf("Escriba el id del bloque al que desea dar contendio: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	if (punteros[id_bloque] != NULL)
	{
		llenar_bytes(punteros[id_bloque], tamanos[id_bloque]);
	}
	else
	{
		printf("Id incorrecto! \n");
	}
}

void mostrar_bytes(void *ptr, int tam)
{
	unsigned char *punt = (unsigned char *)ptr;
	int cont = 0;
	while (cont < tam)
	{
		int lin = 0;
		while (cont < tam && lin < 4)
		{
			int bytes = 0;
			while (cont < tam && bytes < 8)
			{
				printf("%02X ", *(punt + cont));
				cont++;
				bytes++;
			}
			lin++;
			printf("    ");
		}
		printf("\n");
	}
}

void mostrar_contenido()
{
	printf("Escriba el id del bloque del que desea ver el contenido: ");
	int id_bloque;
	scanf("%d", &id_bloque);
	if (punteros[id_bloque] != NULL)
	{
		printf("\n\t\t\tContendio de memoria:\n");
		mostrar_bytes(punteros[id_bloque], tamanos[id_bloque]);
	}
	else
	{
		printf("Id incorrecto! \n");
	}
}
