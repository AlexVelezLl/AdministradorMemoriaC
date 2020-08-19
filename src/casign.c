#include<stdlib.h>
#include<string.h>

/**
 * Funciones que estan en otro archivo
 */
void* memasign(size_t tam);

void* casign(size_t tam){
	void* ptr = memasign(tam);
	memset(ptr,0,tam);
	return ptr;
}
