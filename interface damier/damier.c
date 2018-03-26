#include<stdlib.h>
#include<stdio.h>

void decalage(){
	printf("		");
}
void decalage_num(int j){
	printf("	       %d", j);
}

int main(){
	int i,j;
	for(j=0;j<10;j++){
		decalage();
		for(i=0;i<10;i++){
			if(i!=9)
				printf("+---");
			else
				printf("+---+");
		}

		printf("\n");
		decalage_num(j);
		for(i=0;i<10;i++){
			if(i!=9)
				printf("| . ");
			else
				printf("| . |");
		}
		printf("\n");
	}

return 0;
}
