#include<infoadmin.h>
#include<stdlib.h>
#include<stdio.h>
/**
 * Funciones implementadas en otros archivos
 */
void* memasign(size_t tam);
void actualizar_contiguo_mayor();

/**
 * Funciones que estan en este archivo.
 */
info_bloque* buscar_nodo_prev(void* ptr, int* superbloque_index);

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
void* reasign(void* ptr, size_t tam){
	if(tam<1){
		printf("ERROR - NO SE PUEDE REASIGNAR EL BLOQUE A UN BLOQUE CON UN TAMAÑO MENOR A 1, USE LIBERAR EN VEZ DE REASIGN SI DESEA LIBERAR EL BLOQUE\n");
		return NULL;
	}
	int supernodo_index;
	info_bloque* nodo = buscar_nodo_prev(ptr,&supernodo_index);
	nodo = nodo->siguiente;
	if(nodo == NULL){
		printf("ERROR - %p NO ES UN PUNTERO CREADO CON MEMASIGN\n",ptr);
		return NULL;
	}
	unsigned int tam_actual = nodo-> tam;
	if(tam<=tam_actual){
		nodo->tam = tam;
		nodo->delta += (tam_actual-tam);
		
		admin.info.reasignaciones++;
		admin.info.tam_asign -= (tam_actual-tam);
		admin.info.tam_libre += (tam_actual-tam);
		
		superbloque* super = admin.superbloques;
		super+=supernodo_index;
		if(nodo->delta>super->tam_contiguo_mayor){
			super->tam_contiguo_mayor = nodo->delta;
		}
		actualizar_contiguo_mayor();
	}
	return ptr;
	//unsigned int tam_faltante = tam-tam_actual;
	//if(nodo){
	
	//}
}

/**
 * Funcion que retorna el nodo previo al que pertenezca la
 * direccion ptr.
 *
 * Si el puntero ptr no fue creado con memasign, entonces
 * returna NULL
 */
info_bloque* buscar_nodo_prev(void* ptr,int* superbloque_index){
	*superbloque_index = -1;
	info_bloque* nodo_viajero = admin.lista_bloques.nodos;
	while(nodo_viajero->siguiente!=NULL){
		if(nodo_viajero->tam==0){
			*superbloque_index+=1;
		}
		if(nodo_viajero->siguiente->dir_actual == ptr && nodo_viajero->siguiente->tam!=0){
			return nodo_viajero;
		}
		nodo_viajero = nodo_viajero -> siguiente;
	}
	return NULL;
}



