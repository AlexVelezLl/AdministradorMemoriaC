#include<infoadmin.h>
#include<stdio.h>

info_bloque* reservar_bloque(size_t tam,int superbloque_index);
info_bloque* nodo_libre();
info_bloque* crear_superbloque(size_t tam);
void crear_mas_nodos();
void actualizar_contiguo_mayor();
int obt_num_superbloque();

/**
 * Devuelve el puntero a un  bloque de memoria de tamaño tam
 *
 * Devuelve NULL si tuvo algun error
 */
void* memasign(size_t tam){
	if(admin.superbloques == NULL){
		createadmin();
	}
	
	info_bloque* nodo_nuevo = nodo_libre();
	if(nodo_nuevo == NULL){
		return NULL;
	}
	info_bloque* bloque_anterior;
	int superbloque_index = obt_num_superbloque(tam);	
	if(superbloque_index==-1){
		bloque_anterior = crear_superbloque(tam);
		if(bloque_anterior==NULL){
			return NULL;
		}
	}else{
		bloque_anterior = reservar_bloque(tam,superbloque_index);
	}

	/* Insertando nodo. */ 
	nodo_nuevo->dir_actual = bloque_anterior->dir_actual+bloque_anterior->tam;
	nodo_nuevo->dir_anterior = NULL;
	nodo_nuevo->tam = tam;
	nodo_nuevo->delta = bloque_anterior->delta - tam;
	nodo_nuevo->siguiente = bloque_anterior->siguiente;
	bloque_anterior->delta = 0;
	bloque_anterior->siguiente = nodo_nuevo;
	
	/* Actualizando informacion. */
	admin.lista_bloques.tam_efectivo++;
	admin.info.bloques_util++;
	admin.info.asignaciones++;
	admin.info.tam_asign+=tam;
	admin.info.tam_libre-=tam;
	actualizar_contiguo_mayor();
	return nodo_nuevo->dir_actual;
}

/*
 * Devuelve el indice del superbloque que puede contener
 * ese tamaño
 */
int obt_num_superbloque(size_t tam){
	superbloque* super = admin.superbloques;
	for(int i = 0; i<admin.info.n_superbloques;i++){
		if(super->tam_contiguo_mayor>=tam){
			return i;
		}
		super++;
	}
	return -1;
}

/**
 * separa un bloque de memoria del superbloque del indice mandado
 * por parametro, ademas actualiza la informacion del superbloque
 * contiguo mayor
 */
info_bloque* reservar_bloque(size_t tam, int superbloque_index){
	superbloque* super = admin.superbloques;
	super+=superbloque_index;
	info_bloque* bloque = NULL;
	info_bloque* nodo_viajero = super->nodo_centinela;
	int maximo = 0;
	do{
		if(bloque == NULL && nodo_viajero->delta >= tam){
			bloque = nodo_viajero;
			if(bloque->delta-tam>maximo){
				maximo = bloque->delta - tam;
			}
		}else{
			if(nodo_viajero->delta>maximo){
				maximo = nodo_viajero->delta;
			}
		}
		if(nodo_viajero -> siguiente ==NULL){
			break;
		}
		nodo_viajero = nodo_viajero->siguiente;
	}while(nodo_viajero->tam!=0);

	super->tam_contiguo_mayor = maximo;
	return bloque;
}

void actualizar_contiguo_mayor(){
	int maximo = 0;
	superbloque* super = admin.superbloques;
	for(int i=0; i<admin.info.n_superbloques;i++){
		if((super+i)->tam_contiguo_mayor>maximo){
			maximo = (super+i)->tam_contiguo_mayor;
		}
	}
	admin.info.tam_contiguo_mayor = maximo;
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
