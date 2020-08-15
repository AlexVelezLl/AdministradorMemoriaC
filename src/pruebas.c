#include<stdio.h>
#include<stdlib.h>

void* memasign(size_t tam);
void liberar(void* ptr);
void printstatus();

int main(){
	void* ptrs[270];
	for(int i=0; i<270;i++)	
	ptrs[i] = memasign(100);

	printf("\n\n\nAntes\n");
	printstatus();


	for(int i=0;i<270;i++){
		liberar(ptrs[i]);
	}
	printf("\n\n\nDespues:\n");
	printstatus();
}
