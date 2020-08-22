#include <infoadmin.h>
#include <stdio.h>

void mostrar_estado()
{
    printf("\n╔═════════════════════════════════════════════════╗\n");
    printf("║             ESTADO DEL ADMINISTRADOR            ║\n");
    printf("║                   DE MEMORIA                    ║\n");
    printf("╚═════════════════════════════════════════════════╝\n\n");
    printf("Numero de superbloques usados:\t |%d\n", admin.info.n_superbloques);
    printf("Numero maximo de superbloques:\t |%d\n", admin.info.max_superbloques);
    printf("Numero de bloques utilizados:\t |%d\n", admin.info.bloques_util);
    printf("Numero maximo de bloques:\t |%d\n", admin.info.max_bloques);
    printf("Numero de asignacionees:\t |%d\n", admin.info.asignaciones);
    printf("Numero de reasignaciones:\t |%d\n", admin.info.reasignaciones);
    printf("Numero de liberaciones:\t\t |%d\n", admin.info.liberaciones);
    printf("Numero de desfragmentaciones:\t |%d\n", admin.info.desfragmentaciones);
    printf("Tamaño asignado:\t\t |%d B\n", admin.info.tam_asign);
    printf("Tamaño libre:\t\t\t |%d B\n", admin.info.tam_libre);
    printf("Tamaño contiguo mayor:\t\t |%d B\n\n", admin.info.tam_contiguo_mayor);
}

void mostrar_superbloques()
{
    printf("\n╔═════════════════════════════════════════════════╗\n");
    printf("║             ESTADO DE SUPERBLOQUES              ║\n");
    printf("╚═════════════════════════════════════════════════╝\n\n");
    for (int i = 0; i < admin.info.n_superbloques; i++)
    {
        printf("/t Superbloque %d", i);
        printf("Tamaño:\t\t\t\t |%d\n", (admin.superbloques + i)->tam);
        printf("Tamaño contiguo mayor:\t|%d\n", (admin.superbloques + i)->tam_contiguo_mayor);
        printf("──────────────────────────────\n\n");
    }
}

void mostrar_nodo(void *ptr)
{
    info_bloque *nodo_viajero = admin.lista_bloques.nodos->siguiente;
    while (nodo_viajero != NULL)
    {
        if (nodo_viajero->dir_actual == ptr && nodo_viajero->tam > 0)
        {
            printf("direccion actual:\t |%p\n", nodo_viajero->dir_actual);
            printf("direccion anterior:\t |%p\n", nodo_viajero->dir_anterior);
            printf("tamaño: \t\t |%d\n", nodo_viajero->tam);
        }
        nodo_viajero = nodo_viajero->siguiente;
    }
}
