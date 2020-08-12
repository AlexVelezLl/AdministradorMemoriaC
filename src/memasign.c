#include<stdlib.h>
#include<infoadmin.h>
#include<stdio.h>
void* memasign(size_t tam){
	if(admin.superbloques == NULL){
		createadmin();
	}
}

int main(){
	memasign(sizeof(int));
	printf("%d",admin.superbloques->tam);
}
