typedef struct info_memadmin{
	unsigned int n_superbloques;
	unsigned int max_superbloques;
	unsigned int bloques_util;
	unsigned int max_bloques;
	unsigned int asignaciones;
	unsigned int liberaciones;
	unsigned int desfragmentaciones;
	unsigned int tam_asign;
	unsigned int tam_libre;
	unsigned int tam_contiguo_mayor;
}info_memadmin;

typedef struct info_bloque{
	void* dir_actual;
	void* dir_anterior;
	unsigned int tam;
	unsigned int delta;
	struct info_bloque* siguiente;
} info_bloque;

typedef struct lista{
	info_bloque* nodos;
	unsigned int tam_efectivo;
	unsigned int tam_max;
}lista;

typedef struct superbloque{
	void* ptr;
	unsigned int tam;
	unsigned int tam_contiguo_mayor;
	info_bloque* nodo_centinela;
}superbloque;

typedef struct memadmin{
	info_memadmin info;
	superbloque* superbloques;
	lista lista_bloques;
}memadmin;

memadmin admin;

void createadmin();
