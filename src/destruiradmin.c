#include<infoadmin.h>
#include<stdlib.h>
#include<string.h>

/**
 * Funcion que libera todos los bloques
 * creados por calloc y malloc de nuestro 
 * administrador, [araevitar fugas de memoria.
 */
void destruir_admin(){
	for(int i=0;i<admin.info.n_superbloques;i++){
		free((admin.superbloques+i)->ptr);
	}
	free(admin.superbloques);
	free(admin.lista_bloques.nodos);
	memset(&admin,0,sizeof(memadmin));
}
