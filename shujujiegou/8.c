//顺序表查找算法
// int Sequential_Search(int *a,int n,int key){
// 	int i;
// 	for(i=1;i<=n;i++){
// 		if(a[i]==key)
// 			return i;
// 	}
// 	return 0;
// }
// //有哨兵顺序查找
// int Sequential_Search2(int *a,int n,int key){
// 	int i;
// 	a[0] = key;
// 	i = n;
// 	while(a[i]!=key){
// 		i--;
// 	}
// 	return i;
// }

// //折半查找
// int Binary_Search(int *a,int n,int key){
// 	int low,high,mid;
// 	low = 1;
// 	high = n;
// 	while(low<=high){
// 		mid = (low+high)/2;
// 		//mid = low+(high-low)*(key-a[low])/(a[high]-a[low]);//插值
// 		if(key<a[mid])
// 			high = mid-1;
// 		else if(key>a[mid])
// 			low = mid+1;
// 		else
// 			return mid;
// 	}
// 	return 0;
// }

// //斐波那契查找
// int Fibonacci_Search(int *a,int n,int key){
// 	int low,high,mid,i,k;
// 	low=1;
// 	high=n;
// 	k=0;
// 	//F已计算好的全局变量数组，一组斐波那契数列
// 	while(n<F[k]-1)
// 		k++;
// 	for(i = n;i<F[k]-1;i++)
// 		a[i] = a[n];
// 	while(low<=high){
// 		mid = low+F[k-1]-1;
// 		if(key<a[mid]){
// 			high = mid-1;
// 			k=k-1;
// 		}else if(key>a[mid]){
// 			low=mid+1;
// 			k=k-2;
// 		}else{
// 			if(mid<=n)
// 				return mid;
// 			else
// 				return n;
// 		}
// 	}
// 	return 0;
// }

//二叉查找树
//二叉链表结点结构定义
#include <stdlib.h>
#include <stdio.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef int Status;

//二叉排序树查找
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	if(!T){
		*p = f;
		return 0;
	}else if(key==T->data){
		*p = T;
		return 1;
	}else if(key<T->data)
		return SearchBST(T->lchild,key,T,p);
	else
		return SearchBST(T->rchild,key,T,p);
}
//二叉排序树插入
Status InsertBST(BiTree *T,int key){
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p)){
		s = (BiTree)malloc(sizeof(BiTree));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)
			*T = s;
		else if(key<p->data)
			p->lchild = s;
		else 
			p->rchild = s;
		return 1;
	}else
		return 0;
}

//从二叉排序树中删除结点p，并重接它的左或右子树
Status Delete(BiTree *p){
	BiTree q,s;
	if((*p)->rchild==NULL){
		q = *p;*p=(*p)->lchild;free(q);
	}else if((*p)->lchild==NULL){
		q  = *p;*p=(*p)->rchild;free(q);
	}else{
		q = *p;s=(*p)->lchild;
		while(s->rchild){
			q = s;s=s->rchild;
		}
		(*p)->data = s->data;
		if(q!=*p)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}
	return 1;
}
//二叉排序树删除
Status DeleteBST(BiTree *T,int key){
	if(!*T)
		return 0;
	else{
		if(key==(*T)->data)
			return Delete(T);
		else if(key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
	}
}

//平衡二叉树二叉链表结点结构定义
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//以P为根的二叉排序树作右旋处理
//处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点
void R_Rotate(BiTree *P){
	BiTree L;
	L = (*P)->lchild;
	(*P)->lchild = L->rchild;
	L->rchild = (*P);
	*P = L;
}
//以p为根的二叉排序树作左旋筛
void L_Rotate(BiTree *P){
	BiTree R;
	R = (*P)->rchild;
	(*P)->rchild = R->lchild;
	R->lchild = (*P);
	*P = R;
}
#define LH +1
#define EH 0
#define RH -1

//对以指针T所指结点为根的二叉树作左平衡旋转处理
//本算法结束时，指针T指向新的根结点
void LetBalance(BiTree *T){
	BiTree L,Lr;
	L = (*T)->lchild;

	switch(L->bf){
		case LH:
			(*T)->bf = L->bf=EH;
			R_Rotate(T);
			break;
		case RH:
			Lr = L->rchild;
			switch(Lr->bf){
				case LH:(*T)->bf=RH;
					L->bf = EH;
					break;
				case EH:(*T)->bf=EH;
					L->bf = LH;
					brak;
			}
	}
	Lr->bf = EH;
	L_Rotate(&(*T)->lchild);
	R_Rotate(T);
}
//
Status InsertAVL(BiTree *T,int e,Status *taller){
	if(!*T){
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = 1;
	}else{
		if(e==(*T)->data){
			*taller = 0;
			return 0;
		}
		if(e<(*T)->data){
			if(!InsertAVL(&(*T)->lchild,e,taller))
				return 0;
			if(taller){
				switch((*T)->bf){
					case LH:
						LeftBalance(T);
						*taller = 0;
						break;
					case EH:
						(*T)->bf = LH;
						*taller = TURE;
						break;
					case RH:
						(*T)->bf = EH;
						*taller = 0;
						break;
				}
			}else{
				if(!InsertAVL(&(*T)->rchild,e,taller))
					return 0;
				if(*taller){
					switch((*T)->bf){
						case LH:
							(*T)->bf = EH;
							*taller = 0;
							break;
						case EH:
							(*T)->bf = RH;
							*taller = 1;
							break;
						case RH:
							RightBalance(T);
							*taller = 0;
							break;
					}
				}
			}
		}
	}
	return 1;
}

//散列表查找实现
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12
#define NULLKEY -32768
//结构定义
typedef struct 
{
	int *elem;
	itn count;
}HashTable;
int m =0;
Status InitHashTable(HashTable *H){
	int i;
	m = HASHSIZE;
	H->count = m;
	H->elem = (int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++)
		H->elem[i] = NULLKEY;
	return OK;
}
int Hash(int key){
	return key%m;
}
void InsertHash(HashTable *H,int key){
	int addr = Hash(key);
	while(H->elem[addr]!=NULLKEY)
		addr = (addr+1)%m;
	H->elem[addr] = key;
}
Status SearchHash(HashTable H,int key,int *addr){
	*addr = Hash(key);
	while(H.elem[*addr]!=key){
		*addr = (*addr+1)%m;
		if(H.elem[*addr]==NULLKEY||*addr==Hash(key)){
			return UNSUCCESS;
		}
	}
	return SUCCESS;
}




int main(){
	int i;
	int a[10] = {62,88,58,47,35,73,51,99,37,93};
	BiTree T = NULL;
	// for(i =0;i<10;i++){
	// 	InsertBST(&T,a[i]);
	// }

	Status taller;
	for(i =0;i<10;i++){
		InsertAVL(&T,a[i],&taller);
	}

	return 0;
}

