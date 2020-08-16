#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memadmin.h>

int main(){
	int* a = memasign(4*sizeof(int));
	for(int i=0; i<4;i++){
		*(a+i) = i;
	}	
	destruir_admin();	
}	
