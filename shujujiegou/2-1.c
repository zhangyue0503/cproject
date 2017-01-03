#
#include <stdio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;



int main(){

	

	return 0;
}

typedef struct Node
{
	ElemType data;
	struct Node *next;	
}Node;
typedef struct Node *LinkList;

Status GetElem(LinkList L,int i,ElemType *e){
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while(p && j<1){
		p = p->next;
		++j;
	}
	if(!p || j>i){
		return ERROR;
	}
	*e = p->data;
	return OK;
}

Status ListInsert(LinkList L,int i,ElemTYpe *e){
	int j;
	LinkList p,s;
	p = *L;
	j = 1;
	while（p && j<i）{
		p = p->next;
		++j;
	}
	if(!p || j>i){
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete(LinkList *L ,int i,ElemType *e){
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while(p && j<i){
		p = p->next;
		++j;
	}
	if(!(p->next)||j>i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->next;
	free(q);
	return OK;
}

void CreateListTail(LinkList *L,int n){
	LinkList p,r;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	for(i=0;i<n;i++){
		p = (Node *)malloc(sizeof(Node));
		p->data = rand()*100+1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

void ClearList(LinkList *L){
	LinkList p,q;
	p = (*L)->next;
	while(p){
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = null;
	return OK;
}

