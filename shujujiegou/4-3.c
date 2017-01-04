#include <stdio.h>

//递归斐波那契数列
int Fbi(int i){
	if(i<2)
		return i==0?0:1;
	return Fbi(i-1)+Fbi(i-2);
}

int main(){
	int i;
	for(int i=0;i<6;i++){
		printf("%d\n",Fbi(i) );
	}
	return 0;
}