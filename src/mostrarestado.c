#include <infoadmin.h>
#include <stdio.h>

void mostrar_estado()
{
    printf("\n╔═════════════════════════════════════════════════╗\n");
    printf("║             ESTADO DEL ADMINISTRADOR            ║\n");
    printf("║                   DE MEMORIA                    ║\n");
    printf("╚═════════════════════════════════════════════════╝\n\n");
    printf("numero de superbloques usados:\t |%d\n", admin.info.n_superbloques);
    printf("numero maximo de superbloques:\t |%d\n", admin.info.max_superbloques);
    printf("numero de bloques utilizados:\t |%d\n", admin.info.bloques_util);
    printf("numero maximo de bloques:\t |%d\n", admin.info.max_bloques);
    printf("numero de asignacionees:\t |%d\n", admin.info.asignaciones);
    printf("numero de liberaciones:\t\t |%d\n", admin.info.liberaciones);
    printf("numero de desfragmentaciones:\t |%d\n", admin.info.desfragmentaciones);
    printf("tamaño asignado:\t\t |%d B\n", admin.info.tam_asign);
    printf("tamaño libre:\t\t\t |%d B\n", admin.info.tam_libre);
    printf("tamaño contiguo mayor:\t\t |%d B\n\n", admin.info.tam_contiguo_mayor);
}
