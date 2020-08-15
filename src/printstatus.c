#include<infoadmin.h>
#include<stdio.h>
void printadicional(){
	printf("\n\nAdicional\n");
	printf("Numero de nodos actual de la lista: %d",admin.lista_bloques.tam_efectivo);
	printf("\ndelta de ese nodo: %d\n",admin.lista_bloques.nodos->delta);
	printf("Bloque contiguo mayor del superbloque: %d\n",admin.superbloques->tam_contiguo_mayor);
}

void printstatus(){
	printf("--------Info admin---------\n");
	printf("numero de superbloques usados: %d\n",admin.info.n_superbloques);
	printf("numero maximo de superbloques: %d\n",admin.info.max_superbloques);
	printf("numero de bloques utilizados: %d\n",admin.info.bloques_util);
	printf("numero maximo de bloques: %d\n",admin.info.max_bloques);
	printf("numero de asignacionees: %d\n",admin.info.asignaciones);
	printf("numero de liberaciones: %d\n",admin.info.liberaciones);
	printf("numero de reasignaciones: %d\n",admin.info.reasignaciones);
	printf("numero de desfragmentaciones: %d\n",admin.info.desfragmentaciones);
	printf("tamaño asignado: %d\n",admin.info.tam_asign);
	printf("tamaño libre: %d\n",admin.info.tam_libre);
	printf("tamaño contiguo mayor: %d\n",admin.info.tam_contiguo_mayor);
	printadicional();
}
