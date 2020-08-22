#include <infoadmin.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Funciones implementadas en otros archivos
 */
void *memasign(size_t tam);
void actualizar_contiguo_mayor();
void liberar(void *ptr);

/**
 * Funciones que estan en este archivo.
 */
info_bloque *buscar_nodo_prev(void *ptr, int *superbloque_index);
unsigned int delta_mayor(info_bloque *centinela);
void copiar_bytes(void *ptr1, void *ptr2, int n);

/**
 * Funcion que reasigna el tamaño de un bloque
 * creado con memasign y devuelve el puntero del
 * nuevo bloque donde esta reasignado.
 *
 * Es importante notar que el puntero puede como no
 * devolver la misma direccion de memoria.
 *
 * La funcion retorna NULL si el puntero pasado no fue
 * creado con memasign, o si el tamaño es menor que 1.
 */
void *reasignar(void *ptr, size_t tam)
{
	if (admin.superbloques == NULL)
	{
		createadmin();
	}
	if (tam < 1)
	{
		printf("ERROR - NO SE PUEDE REASIGNAR EL BLOQUE A UN BLOQUE CON UN TAMAÑO MENOR A 1, USE LIBERAR EN VEZ DE REASIGN SI DESEA LIBERAR EL BLOQUE\n");
		return NULL;
	}
	int supernodo_index;
	info_bloque *nodo = buscar_nodo_prev(ptr, &supernodo_index);
	if (nodo == NULL)
	{
		printf("ERROR - %p NO ES UN PUNTERO CREADO CON MEMASIGN\n", ptr);
		return NULL;
	}
	nodo = nodo->siguiente;
	unsigned int tam_actual = nodo->tam;
	unsigned int pot_tam_bloque = nodo->tam + nodo->delta;
	if (tam <= pot_tam_bloque)
	{
		nodo->tam = tam;
		nodo->delta += (tam_actual - tam);

		admin.info.reasignaciones++;
		admin.info.tam_asign -= (tam_actual - tam);
		admin.info.tam_libre += (tam_actual - tam);

		superbloque *super = admin.superbloques;
		super += supernodo_index;
		if (tam_actual >= tam)
		{
			if (nodo->delta > super->tam_contiguo_mayor)
			{
				super->tam_contiguo_mayor = nodo->delta;
			}
		}
		else
		{
			super->tam_contiguo_mayor = delta_mayor(super->nodo_centinela);
		}
		actualizar_contiguo_mayor();
		return ptr;
	}
	void *ptr_nuevo = memasign(tam);
	copiar_bytes(nodo->dir_actual, ptr_nuevo, tam_actual);
	liberar(nodo->dir_actual);

	admin.info.asignaciones--;
	admin.info.liberaciones--;
	admin.info.reasignaciones++;
	return ptr;
}

/**
 * Funcion que retorna el nodo previo al que pertenezca la
 * direccion ptr.
 *
 * Si el puntero ptr no fue creado con memasign, entonces
 * returna NULL
 */
info_bloque *buscar_nodo_prev(void *ptr, int *superbloque_index)
{
	*superbloque_index = -1;
	info_bloque *nodo_viajero = admin.lista_bloques.nodos;
	while (nodo_viajero->siguiente != NULL)
	{
		if (nodo_viajero->tam == 0)
		{
			*superbloque_index += 1;
		}
		if (nodo_viajero->siguiente->dir_actual == ptr && nodo_viajero->siguiente->tam != 0)
		{
			return nodo_viajero;
		}
		nodo_viajero = nodo_viajero->siguiente;
	}
	return NULL;
}

/**
 * Busca el mayor delta que haysa en un superbloque
 * a partir de su nodo centinela. Este mayor delta
 * representara el tamaño contiguo mayor del 
 * superbloque
 */
unsigned int delta_mayor(info_bloque *centinela)
{
	unsigned int maximo = 0;
	info_bloque *nodo_viajero = centinela->siguiente;
	while (nodo_viajero != NULL && nodo_viajero->tam > 0)
	{
		if (nodo_viajero->delta > maximo)
		{
			maximo = nodo_viajero->delta;
		}
		nodo_viajero = nodo_viajero->siguiente;
	}
	return maximo;
}

/*
 * Copia los n primeros bytes desde ptr1 a ptr2
 */
void copiar_bytes(void *ptr1, void *ptr2, int n)
{
	unsigned char *ptrsrc = (unsigned char *)ptr1;
	unsigned char *ptrdes = (unsigned char *)ptr2;
	for (int i = 0; i < n; i++)
	{
		*ptrdes++ = *ptrsrc++;
	}
}
