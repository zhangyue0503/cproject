//双亲表示法
#define MAX_TREE_SIZE 100;
typedef int TElemType;
tyepdef struct PTNode
{
	TElemType data;
	int parent;	
}PTNode;
typedef struct 
{
	PTNode nodes[MAX_TREE_SIZE];
	int r,n;
}PTree;

//孩子表示法
typedef struct CTNode
{
	int child;
	struct CTNode *next;
}*ChildPtr;
typedef struct 
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;
typedef struct 
{
	CTBox nodes[MAX_TREE_SIZE];
	int r,n;
}CTree;

//孩子兄弟表示法
typedef struct CSNode
{
	TElemType data;
	struct CSNode *fristchild,*rightsib;
}CSNode,*CSTree;

//二叉链表存储结构
typedef struct BiTnode
{
	TElemType data;
	struct BiTNode *lchild,*rchild;
};

//前序遍历
void ProOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	printf("%c",T->data );
	ProOrderTraverse(T->lchild);
	ProOrderTraverse(T->rchild);
}

//中序遍历
void InOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data );
	InOrderTraverse(T->rchild);
}

//后序遍历
void PostOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data );
}

//创建二叉树
void CreateBiTree(BiTree *T){
	TElemType ch;
	scanf("%c",&ch);
	if(ch=='#')
		*T = NULL;
	else{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!*T){
			exit(OVERFLOW);
		}
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

//线索二叉树数据结构
typedef enum {Link,Thread} PointerTag;
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag;
	PointerTag RTag;
}BiThrNode ,*BiThrTree;

//中序遍历线索化
BiThrTree pre;
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);
		if(!p->lchild){
			p->LTag = Thread;
			p->lchild = pre;
		}
		if(!pre->rchild){
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
//线索二叉树遍历
Status InOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p = T->lchild;
	while(p!=T){
		while(p->LTag==Link)
			p = p->lchild;
		printf("%c", p->data);
		while(p->RTag==Thread&&p->rchild!=T){
			p = p->rchild;
			printf("%c", p->data);
		}
		p = p->rchild;
		
	}
	return OK;
}




