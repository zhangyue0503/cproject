#include <stdlib.h>
#include <stdio.h>
//排序用到的结构与函数
#define MAXSIZE 10
typedef struct 
{
	int r[MAXSIZE+1];
	int length;
}SqList;

void swap(SqList *L,int i,int j){
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

//对顺序表L作交换排序（冒泡排序初级版）
void BubbleSort0(SqList *L){
	int i,j;
	for(i=0;i<L->length;i++){
		for(j=i;j<=L->length-1;j++){
			if(L->r[i]>L->r[j]){
				swap(L,i,j);
			}
		}
	}
}
//正宗排序算法
void BubbleSort(SqList *L){
	int i,j;
	for(i=0;i<L->length;i++){
		for(j=L->length-2;j>=i;j--){
			if(L->r[j]>L->r[j+1]){
				printf("%d,%d\n",L->r[j],L->r[j+1] );
				swap(L,j,j+1);
			}
		}
		printf("%d\n",L->r[i] );
	}
}
typedef int Status;
//改进冒泡
void BubbleSort2(SqList *L){
	int i,j;
	Status flag = 1;
	for(i=0;i<L->length&&flag;i++){
		flag = 0;
		for(j=L->length-2;j>=i;j--){
			if(L->r[j]>L->r[j+1]){
				swap(L,j,j+1);
				flag = 1;
			}
		}
	}
}

//简单选择排序
void SelectSort(SqList *L){
	int i,j,min;
	for(i=0;i<L->length-1;i++){
		min = i;
		for(j=i+1;j<=L->length-1;j++){
			if(L->r[min]>L->r[j])
				min = j;
		}
		if(i!=min)
			swap(L,i,min);
	}
	
}
//直接插入排序
void InsertSort(SqList *L){
	int i,j;
	for(i=2;i<=L->length-1;i++){
		if(L->r[i]<L->r[i-1]){
			L->r[0] = L->r[i];
			for(j=i-1;L->r[j]>L->r[0];j--)
				L->r[j+1] = L->r[j];
			L->r[j+1] = L->r[0];
		}
	}
}

//希尔排序
void ShellSort(SqList *L){
	int i,j;
	int increment = L->length;
	do{
		increment = increment/3+1;
		for(i=increment+1;i<=L->length;i++){
			if(L->r[i]<L->r[i-increment]){
				L->r[0] = L->r[i];
				for(j=i-increment;j>0&&L->r[0]<L->r[j];j-=increment)
					L->r[j+increment] = L->r[j];
				L->r[j+increment] = L->r[0];
			}
		}
	}while(increment>1);
}
//堆调整
void HeapAdjust(SqList *L,int s ,int m){
	int temp,j;
	temp = L->r[s];
	for(j=2*s;j<=m;j*=2){
		if(j<m && L->r[j]<L->r[j+1])
			++j;
		if(temp>=L->r[j])
			break;
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;
}
//堆排序
void HeapSort(SqList *L){
	int i;
	for(i=L->length/2;i>0;i--)
		HeapAdjust(L,i,L->length);
	for(i=L->length;i>1;i--){
		swap(L,1,i);
		HeapAdjust(L,1,i-1);
	}
}


//
void Merge(int SR[],int TR[],int i,int m,int n){
	int j,k,l;
	for(j = m+1,k=i;i<=m&&j<=n;k++){
		if(SR[i]<SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if(i<m){
		for(l=0;l<=m-i;l++)
			TR[k+l] = SR[i+l];
	}
	if(j<=n){
		for(l=0;l<=n-j;l++)
			TR[k+l] = SR[j+l];
	}
}
//
void MSort(int SR[],int TR1[],int s,int t){
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s] = SR[s];
	else{
		m = (s+t)/2;
		MSort(SR,TR2,s,m);
		MSort(SR,TR2,m+1,t);
		Merge(TR2,TR1,s,m,t);
	}
}

//归并排序
void MergeSort(SqList *L){
	MSort(L->r,L->r,1,L->length);
}

//非递归实现归并排序
void MergePass(int SR[],int TR[],int s,int n){
	int i = 1;
	int j;
	while(i<=n-2*s+1){
		Merge(SR,TR,i,i+s-1,i+2*s-1);
		i=i+2*s;
	}
	if(i<n-s+1)
		Merge(SR,TR,i,i+s-1,n);
	else
		for(j=i;j<=n;j++)
			TR[j] = SR[j];
}
void MergeSort2(SqList *L){
	int* TR = (int*)malloc(L->length*sizeof(int));
	int k = 1;
	while(k<L->length){
		MergePass(L->r,TR,k,L->length);
		k=2*k;
		MergePass(TR,L->r,k,L->length);
		k=2*k;
	}
}


//快速排序
int Partition(SqList *L,int low,int high){
	int pivotkey;
	pivotkey = L->r[low];
	while(low<high){
		while(low<high&&L->r[high]>=pivotkey)
			high--;
		swap(L,low,high);
		while(low<high&&L->r[low]<=pivotkey)
			low++;
		swap(L,low,high);
	}
	return low;
}
void QSort(SqList *L,int low,int high){
	int pivot;
	if(low<high){
		pivot = Partition(L,low,high);
		QSort(L,low,pivot-1);
		QSort(L,pivot+1,high);
	}
}
void QuickSort(SqList *L){
	QSort(L,0,L->length-1);
}



int main(){
	SqList L = {
		.r = {62,88,58,47,35,73,51,99,37,93},
		// .r = {50,10,90,30,70,40,80,60,20},
		.length = 10
	};

	// for(int i=0;i<10;i++){
	// 	printf("%d\n",L.r[i] );
	// }

	// BubbleSort0(&L);
	// BubbleSort2(&L);
	// BubbleSort(&L);
	// SelectSort(&L);
	// HeapSort(&L);
	// MergeSort2(&L);
	QuickSort(&L);
	for(int i=0;i<10;i++){
		printf("%d\n",L.r[i] );
	}

	// SqList L1 = {
	// 	.r = {0,5,3,4,6,2},
	// 	.length = 6
	// };

	// InsertSort(&L1);

	// for(int i=0;i<6;i++){
	// 	printf("%d\n",L1.r[i] );
	// }
	

	// SqList L2 = {
	// 	.r = {0,62,88,58,47,35,73,51,99,37},
	// 	.length = 9
	// };
	// ShellSort(&L2);
	// for(int i=1;i<10;i++){
	// 	printf("%d\n",L2.r[i] );
	// }

	


	return 0;
}
