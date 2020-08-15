#include<infoadmin.h>
#include<stdlib.h>
void createadmin(){
	info_memadmin info = {
		.n_superbloques = 1,
		.max_superbloques = 5,
		.bloques_util = 0,
		.max_bloques = 128,
		.asignaciones = 0,
		.reasignaciones = 0,
		.liberaciones = 0,
		.desfragmentaciones = 0,
		.tam_asign = 0,
		.tam_libre = 1048576,
		.tam_contiguo_mayor = 1048576
	};
	admin.info = info;

	admin.superbloques = (superbloque*) calloc(5,sizeof(superbloque));
	void *primer_bloque = malloc(1048576);
	
	info_bloque* infobloques = (info_bloque*)calloc(128,sizeof(info_bloque));	

	infobloques -> dir_actual = primer_bloque;
	infobloques -> dir_anterior = NULL;
	infobloques -> tam = 0;
	infobloques -> delta = 1048576;
	infobloques -> siguiente = NULL;
	
	admin.superbloques -> ptr = primer_bloque;
	admin.superbloques -> tam = 1048576;
	admin.superbloques -> tam_contiguo_mayor = 1048576;
	admin.superbloques -> nodo_centinela = infobloques;
	
	
	lista lista_bloques = {
		.nodos = infobloques,
		.tam_efectivo = 1,
		.tam_max = 128,
		.ultimo = infobloques
	};

	admin.lista_bloques = lista_bloques;
}
