#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<infoadmin.h>

/**
 * Funciones implementadas en otros archivos
 */
unsigned int delta_mayor(info_bloque* centinela);
void copiar_bytes(void* ptr1, void* ptr2,int n);

/**
 * Funciones implementadas en este archivo
 */
void remover_superbloques(info_bloque* ultimos_nodos[]);
void act_todos_contiguos();

/*
 * Metodo que desfragmenta la memoria y actualiza
 * los punteros de cada bloque con la memoria des
 * fragmentada;
 */
void desfragmentar(){
	int n_superb = admin.info.n_superbloques;
	info_bloque* ultimos_superbloques[n_superb];
	info_bloque* nodo_viajero = admin.lista_bloques.nodos;
	int cont_superb = 0;
	while(nodo_viajero->siguiente!=NULL){
		info_bloque* siguiente = nodo_viajero -> siguiente;
		if(siguiente->tam ==0){
			ultimos_superbloques[cont_superb] = nodo_viajero;
			nodo_viajero = siguiente;
			cont_superb++;
			continue;
		}
		for(int i=0;i<cont_superb;i++){
			info_bloque* ultimo = ultimos_superbloques[i];
			unsigned int tam_superb = ultimo->delta;
			if(siguiente->tam<=tam_superb){
				copiar_bytes(siguiente->dir_actual,ultimo->dir_actual+ultimo->tam,siguiente->tam);
				nodo_viajero->siguiente = siguiente->siguiente;
				siguiente->siguiente = ultimo->siguiente;
				ultimo->siguiente = siguiente;
				nodo_viajero->delta = siguiente->tam + siguiente->delta;
				siguiente->delta = ultimo->delta - siguiente->tam;
				siguiente->dir_anterior = siguiente->dir_actual;
				siguiente->dir_actual = ultimo->dir_actual + ultimo->tam;
				ultimo -> delta = 0;
				ultimos_superbloques[i] = siguiente;
				if(siguiente == admin.lista_bloques.ultimo){
					admin.lista_bloques.ultimo = nodo_viajero;
				}
				break;
			}

		}

		if(nodo_viajero->siguiente!=siguiente){
			continue;
		}

		if(nodo_viajero->delta>0){
			copiar_bytes(siguiente->dir_actual,nodo_viajero->dir_actual+nodo_viajero->tam,siguiente->tam);
			siguiente->delta += nodo_viajero->delta;
			siguiente->dir_anterior = siguiente->dir_actual;
			siguiente->dir_actual = nodo_viajero->dir_actual+nodo_viajero->tam;
			nodo_viajero->delta = 0;
		}
		nodo_viajero = siguiente;
	}
	ultimos_superbloques[n_superb-1] = nodo_viajero;
	remover_superbloques(ultimos_superbloques);
	
	act_todos_contiguos();
	admin.info.desfragmentaciones+=1;
}

/**
 * Fucion que remueve todos los superbloques que esten vacios
 * y que el anterior superbloque este a menos del 80% de capa
 * cidad completada
 *
 * Recibe como atributo a un array con los nodos anteriores a
 * los centinela de cada superbloque.
 */
void remover_superbloques(info_bloque* ultimos_nodos[]){
	int j = 1;
	for(int i=1;i<admin.info.n_superbloques;i++){
		superbloque* super = admin.superbloques;
		super+=j;
		info_bloque* ultimo = ultimos_nodos[i];
		if(ultimo == super->nodo_centinela){
			int tam_libre_ant = (ultimos_nodos[i-1])->delta;
			int tam_tot_ant = (super-1)->tam;
			double porc_usado = tam_libre_ant/tam_tot_ant;
			if(porc_usado<0.8){
				free(super->ptr);
				info_bloque* ult = ultimos_nodos[j-1];
				if(ult->siguiente == NULL){
					ult->siguiente = NULL;
					admin.lista_bloques.ultimo = ult;
				}else{
					ult->siguiente = ult->siguiente->siguiente;
				}
				admin.info.tam_libre-=super->tam;
				admin.lista_bloques.tam_efectivo -=1;
				admin.info.n_superbloques-=1;
				memset(super,0,sizeof(superbloque));
				for(int k =j; k<admin.info.n_superbloques;k++){
					admin.superbloques[k] = admin.superbloques[k+1];
				}
				j--;
			}
		}
		j++;
	}
}

/**
 * Funcion que actualiza los valores de tamaño contiguo
 * mayor de todos los superbloques, y ademas actualiza
 * el tamaño contiguo mayor del administrador general.
 */
void act_todos_contiguos(){
	unsigned int maximo = 0;
	superbloque* super = admin.superbloques;
	for(int i=0;i<admin.info.n_superbloques;i++){
		unsigned int delta = delta_mayor(super->nodo_centinela);
		(admin.superbloques+i)->tam_contiguo_mayor = delta;
		if(delta>maximo){
			maximo = delta;
		}
		super++;
	}
	admin.info.tam_contiguo_mayor = maximo;
}
