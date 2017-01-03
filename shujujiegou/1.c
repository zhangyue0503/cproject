#include <stdio.h>

int main(){
	
	//求1-100
	int i,sum = 0,n=100;
	sum = (1+n)*n/2;
	printf("%d\n",sum);

	i = 2;
	printf("%p\n", &i);
	printf("%d\n", i);

	

	return 0;
}