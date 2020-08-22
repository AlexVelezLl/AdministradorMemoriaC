#include <stdlib.h>
#include <infoadmin.h>
#include <stdio.h>

void *nueva_dir(void *ant_ptr)
{
	if(admin.superbloques == NULL){
		createadmin();
	}
	info_bloque *nodo_viajero = admin.lista_bloques.nodos;
	int es_dir_actual = 0;
	while (nodo_viajero != NULL)
	{
		if (ant_ptr == nodo_viajero->dir_anterior)
		{
			return nodo_viajero->dir_actual;
		}
		if (ant_ptr == nodo_viajero->dir_actual && nodo_viajero->tam > 0)
		{
			es_dir_actual = 1;
		}
		nodo_viajero = nodo_viajero->siguiente;
	}

	if (es_dir_actual == 1)
	{
		return ant_ptr;
	}
	printf("ERROR! El puntero enviado no es una direccion creada con memasign o casign\n");
	return NULL;
}
