#include<infoadmin.h>
#include<stdio.h>
#include<stdlib.h>

/**
 * funciones implementadas en otros archivos
 */
info_bloque* buscar_nodo_prev(void* ptr, int* superbloque_index);
void actualizar_contiguo_mayor();

void liberar(void* ptr){
	int superbloque_index;
	info_bloque* nodo = buscar_nodo_prev(ptr,&superbloque_index);
	if(nodo==NULL){
		printf("ERROR - EL PUNTERO NO ES UN PUNTERO CREADO CON MEMASIGN O YA HA SIDO LIBERADO ANTEIRORMENTE\n");
		return;
	}

	info_bloque* nodo_borrar = nodo->siguiente;
	admin.info.bloques_util--;
	admin.info.liberaciones++;
	admin.info.tam_asign -= nodo_borrar->tam;
	admin.info.tam_libre += nodo_borrar->tam;

	nodo->delta += nodo_borrar->tam + nodo_borrar->delta;
	superbloque* super = admin.superbloques;
	super+=superbloque_index;
	if(nodo->delta>super->tam_contiguo_mayor){
		super->tam_contiguo_mayor = nodo-> delta;
	}
	actualizar_contiguo_mayor();

	nodo->siguiente = nodo_borrar->siguiente;
	if(nodo_borrar->siguiente == NULL){
		admin.lista_bloques.ultimo = nodo;
	}
	admin.lista_bloques.tam_efectivo--;

	nodo_borrar->dir_actual = NULL;
	nodo_borrar->dir_anterior = NULL;
	nodo_borrar->tam = 0;
	nodo_borrar->delta = 0;
	nodo_borrar->siguiente = NULL;

}
