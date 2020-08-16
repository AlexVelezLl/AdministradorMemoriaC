#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void* memasign(size_t tam);
void liberar(void* ptr);
void printstatus();
void* reasignar(void* ptr, size_t tam);
void* memasign(size_t tam);
void desfragmentar();
int main(){
	
	void*ptr1 = memasign(1000);
	void*ptr2 = memasign(1050678);
	void*ptr3 = memasign(1200);
	void*ptr4 = memasign(1050678);
	
	liberar(ptr2);
	printstatus();
	desfragmentar();
	
	printf("\n\n\n\n\n");
	printstatus();

	memasign(1);
	printstatus();
}	
