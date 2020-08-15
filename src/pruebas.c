#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void* memasign(size_t tam);
void liberar(void* ptr);
void printstatus();
void* reasignar(void* ptr, size_t tam);

int main(){

	int* ptr =(int*)memasign(20*sizeof(int));
	for(int i=0;i<20;i++)
		*(ptr+i) = i;
	printf("Antes de reasignar: \n");
	printstatus();
	ptr = reasignar(ptr,25*sizeof(int));
	memset(ptr+20,0,5);
	printf("Despues de reasignar: \n");
	printstatus();
	for(int i=0;i<25;i++){
		printf("%d\n",*(ptr+i));
	}
}	
