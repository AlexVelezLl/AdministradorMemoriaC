#include<infoadmin.h>
#include<stdio.h>

info_bloque* buscar_bloque(size_t tam);
info_bloque* nodo_libre();
info_bloque* crear_superbloque(size_t tam);
void crear_mas_nodos();


void* memasign(size_t tam){
	if(admin.superbloques == NULL){
		createadmin();
	}
	
	info_bloque* nodo_nuevo = nodo_libre();
	info_bloque* bloque_anterior = buscar_bloque(tam);
	if(bloque_anterior==NULL){
		return NULL;
	}
	
	nodo_nuevo->dir_actual = bloque_anterior->dir_actual+tam;
	nodo_nuevo->dir_anterior = NULL;
	nodo_nuevo->tam = tam;
	nodo_nuevo->delta = bloque_anterior->delta - tam;
	nodo_nuevo->siguiente = bloque_anterior->siguiente;

	bloque_anterior->delta = 0;
	bloque_anterior->siguiente = nodo_nuevo;

	admin.lista_bloques.tam_efectivo++;	
	return nodo_nuevo->dir_actual;
}


/*
 * Busca el primer bloque cuyo delta sea menor o igual que 
 * tam, si no encuentra ningun bloque retorna NULL
 */
info_bloque* buscar_bloque(size_t tam){
	info_bloque* n_viajero = admin.lista_bloques.nodos;
	while(n_viajero!=NULL){
		if(n_viajero->tam<=tam){
			return n_viajero;
		}
		n_viajero++;
	}
	return crear_superbloque(tam);
}

/**
 * Funcion que crea un nuevo superbloque de acuerdo al
 * tamaño necesitado (se escoge el maximo entre el tamaño
 * necesitado multiplicado por 1.5 y 1MB) y devuelve el nodo
 * centinela en la lista correspondiente a este superbloque.
 *
 * Retorna NULL si no pudo crear el nuevo superbloque
 */
info_bloque* crear_superbloque(size_t tam){

}

/**
 * Metodo que busca un nodo libre dentro del array 
 * de nodos que estan en el stack.
 * 
 * Este metodo se realiza para poder tener todos los
 * nodos de la lista en un bloque de memoria contigua,
 * y luego solo buscar los que esten libres, para evitar
 * crear cada nodo de la lista con malloc
 */
info_bloque* nodo_libre(){
	info_bloque* n_viajero = admin.lista_bloques.nodos;
	for(int i=0; i<admin.lista_bloques.tam_max;i++){
		if(n_viajero->dir_actual==NULL){
			return n_viajero;
		}
		n_viajero++;
	}
	int max_actual = admin.lista_bloques.tam_max;
	crear_mas_nodos();
	return admin.lista_bloques.nodos+max_actual;
}

/**
 * Funcion que aumenta el tamaño en el heap destinado a
 * guardar los nodos de la lista al doble del tamaño actual,
 * ademas actualiza todas las referencias asociadas a esos nodos
 */
void crear_mas_nodos(){

}


int main(){
	int*a = (int*)memasign(10*sizeof(int));
	
	for(int i = 0; i<10; i++){
		*(a+i) = i;
	}

	for(int i = 0; i<10; i++){
		printf("%d",*(a+i));
	}
}
