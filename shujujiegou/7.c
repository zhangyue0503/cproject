//邻接矩阵存储结构
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100;
#define INFINITY 65535;
typedef struct 
{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

//无向网图的邻接矩阵表示
void CreateMGraph(MGraph *G){
	int i,j,k,w;
	printf("输入顶点数和边数：\n");
	scanf("%d,%d\n", &G->numVertexes,&G->numEdges);

	for(i=0;i<G->numVertexes;i++)
		scanf(&G->vexs[i]);
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
			G->arc[i][j] = INFINITY;

	for(k=0;k<G->numEdges;k++){
		printf("输入边(vi,vj)上的下标i，下标j和权w：\n");
		scanf("%d,%d,%d",&i,&j,&w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}

}

//邻接表存储结构
typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode
{
	VertexType data;
	EdgeNode *firstedge;	
}VertexNode,AdjList[MAXVEX];
typedef struct 
{
	AdjList adjList;
	int numVertexes,numEdges;
}GraphAdjList;

void CreateALGraph(GraphAdjList *G){
	int i,j,k;
	printf("输入顶点数和边数：\n");
	scanf("%d,%d\n", &G->numVertexes,&G->numEdges);

	for(i=0;i<G->numVertexes;i++){
		scanf(&G->adjList[i].data);
		G->adjList[i].firstedge = NULL;
	}

	for(k=0;k<G->numEdges;k++){
		printf("输入边(vi,vj)上的顶点序号：\n");
		scanf("%d,%d",&i,&j);

		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;

		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjList[i].firstedge;
		e->adjList[i].firstedge = e;
	}
}

//邻接矩阵深度优先遍历
typedef int Boolean;
Boolean visited[MAX];
void DFS(MGraph G,int i){
	int j;
	visited[i] = TRUE;
	printf("%c ",G.vex[i]);
	for(j=0;j<G.numVertexes;j++)
		if(G.arc[i][j] == 1 && !visited[j])
			DFS(G,j);
}
void DFSTraverse(MGraph G){
	int i;
	for(i=0;i<G.numVertexes;i++)
		visited[i] = FALSE;
	for(i=0;i<G.numVertexes;i++)
		if(!visited[i])
			DFS(G,i);
}
//邻接表深度优先遍历
void DFS(GraphAdjListGL,int i){
	EdgeNode *p;
	visited[i] = TRUE;
	printf("%c ",GL->adjList[i].data );
	p = GL->adjList[i].firstedge;
	while(p){
		if(!visited[p->adjvex])
			DFS(GL,p->adjvex);
		p = p->next;
	}
}
void DFSTraverse(GraphAdjList GL){
	int i;
	for(i=0;i<GL->numVertexes;i++)
		visited[i] = FALSE;
	for(i=0;i<GL->numVertexes;i++)
		if(!visited[i])
			DFS(GL,i);
}
//邻接矩阵广度优先遍历
void BFSTraverse(MGraph G){
	int i,j;
	Queue Q;
	for(i=0;i<G.numVertexes;i++)
		visited[i] = FALSE;
	InitQueue(&Q);
	for(i=0;i<G.numVertexes;i++){
		if(!visited[i]){
			visited[i] = TRUE;
			printf("%c ", G.vexs[i]);
			EnQueue(&Q,i);
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);
				for(j=0;j<G.numVertexes;j++){
					if(G.arc[i][j]==1 && !visited[j]){
						visited[j]=TRUE;
						printf("%c ",G.vexs[j] );
						EnQueue(&Q,j);
					}
				}
			}
		}
	}
}
//邻接表广度优先遍历
void BFSTraverse(GraphAdjList GL){
	int i;
	EdgeNode *p;
	Queue Q;
	for(i=0;i<GL->numVertexes;i++)
		visited[i] = FALSE;
 	InitQueue(&Q);
 	for(i=0;i<GL->numVertexes;i++){
 		if(!visited[i]){
 			visited[i] = TRUE;
 			printf("%c ",GL->adjList[i].data );
 			EnQueue(&Q,i);
 			while(p){
 				if(!visited[p->adjvex]){
 					visited[p->adjvex] = TRUE;
 					printf("%c ",GL->adjList[p->adjvex].data );
 					EnQueue(&q,p->adjvex);
 				}
 				p = p->next;
 			}
 		}
 	}
}
//Prim算法生成最小生成树
void MiniSpanTree_Prim(MGraph G){
	int min,i,j,k;
	int adjvex[MAXVEX]; //保存相关顶点下标
	int lowcost[MAXVEX];//保存相关顶点边的权值
	lowcost[0] = 0; //初始化第一个权值为0，即v0加入生成树
					/*lowcost的值为0，在这里就是此下标的顶点已经加入生成树*/
	adjvex[0] = 0;//初始化第一个顶点下标为0
	for(i=1;i<G.numVertexes;i++){//循环除下标为0外的全部顶点
		lowcost[i] = G.arc[0][i];//将v0顶点与之有边的可能会存入数组
		adjvex[i] = 0;//初始化都为v0的下标
	}
	for(i=1;i<G.numVertexes;i++){
		min = INFINITY;//初始化最小可能会为无限 
						/*通常设置为不可能的大数字如32767、65535等*/
		j=1;k=0;
		while(j<G.numVertexes){ //循环全部顶点
			if(lowcost[j]!=0&&lowcost[j]<min){ //如果可能会不为0且权值小球min
				min = lowcost[j];//则让当前可能会成为最小值
				k=j;//将当前最小值的下标存入k
			}
			j++;
		}
		printf("(%d,%d)",adjvex[k],k );//打印当前顶点边中权值最小边
		lowcost[k] = 0;//将当前顶点的权值设置为0，表示此顶点已经完成任务
		for(j=1;j<G.numVertexes;j++){
			if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j]){//若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
				lowcost[j] = G.arc[k][j];//将较小权值存入lowcost
				adjvex[j] = k;//将下标为k的顶点存入adjvex
			}
		}
}

//对边集数组Edge结构的定义
typedef struct 
{
	int begin;
	int end;
	int weight;
}Edge;

typedef int MAXEDGE = 15;
//Kruskal算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G){
	int i,n,m;
	Edge edges[MAXEDGE];//定义边集数组
	int parent[MAXVEX];//定义一数组用来判断边与边是否形成环路
	//此处省略将邻接矩阵G转化为边数组edges并按权由小到大排序的代码
	for(i=0;i<G.numVertexes;i++)
		parent[i] = 0;//初始化数组值为0
	for(i=0;i<G.numEdges;i++){//循环每一条边
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i];.end);
		if(n!=m){//假如n与m不等，说明此边没有与再有生成树形成环路
			parent[n] = m;//将此边的结尾顶点放入下标为起点的parent中
							//表示此顶点已经在生成树集合中
			printf("(%d,%d) %d",edges[i].begin,edges[i].end,edges[i].weight);
		}
	}
}
int Find(int *parent,int f){ //查找连线顶点的尾部下标
	while(parent[f]>0)
		f = parent[f];
	return f;
}

//迪杰斯特拉最最短路径算法
#define MAXVEX 9;
#define INFINITY 65535;
typedef int Pathmatirx[MAXVEX];//用于存储最短路径下标的数组
typedef int ShortPathTable[MAX];//用过存储到各点最短路径的权值和
//Dijkstra算法，求有向网G的v0顶点到其余顶点v最短路径P[v]及带权长度D[v]
//P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
void ShortPath_Dijkstra(MGraph G,int v0,Pathmarirx *P,ShortPathTable *D){
	int v,w,k,min;
	int final[MAXVEX];//final[w]=1表示求得顶点v0至vw的最短路径
	for(v=0;v<G.numVertexes;v++){//初始化数据
		final[v] = 0;//全部顶点初始化为未知最短路径状态
		(*D)[v] = G.matirx[v0][v];//将与v0点有国家线的顶点加上仅值
		(*P)[v] = 0;//初始化路径数组P为0
	}
	(*D)[v0] = 0;//v0至v0路径为0
	final[v0] = 1;//v0至v0不需要求路径
	for(v=1;v<G.numVertexes;v++){
		min = INFINITY;//当前所知离v0顶点的最近距离
		for(w=0;w<G.numVertexes;w++){//寻找离v0最近的顶点
			if(!final[w] && (*D)[w]<min){
				k=w;
				min = (*D)[w];//w顶点离v0顶点更近
			}
		}
		final[k] = 1;//将目前找到的最近顶点置为1
		for(w=0;w<G.numVertexes;w++){//修正当前最短路径及距离
			//如果经过v顶点的路径比现在这条路径的长度短的话
			if(!final[w] && (min+G.marirx[k][w]<(*D)[w])){
				//说明找到了更短的路径，修改D[w]和P[w]
				(*D)[w] = min+G.matirx[k][w];//修改当前路径长度
				(*P)[w] = k;
			}
		}
	}
}

//弗洛伊德最短路径算法
typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
//Floyd算法，求网图G中各有顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
void Short_Floyd(MGraph G,Pathmatirx *P,ShortPathTable *D){
	int v,w,k;
	for(v=0;v<G.numVertexes;++v){//初始化D与P
		for(w=0;w<G.numVertexes;++w){
			(*D)[v][w]=G.marirx[v][w];
			(*P)[v][w] = w;
		}
	}
	for(k=0;k<G.numVertexes;++k){
		for(v=0;v<G.numVertexes;++v){
			for(w=0;w<G.numVertexes;++w){
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w]){
					//如果经过下标为k顶点路径比原两点间路径更短
					//将当前两点间权值设为最小的一个
					(*D)[v][w] = (*D)[v][k]+(*D)[k][w];
					(*P)[v][w] = (*P)[v][k];//路径设置经过下标为k的顶点
				}
		}
	}
}
//拓扑排序数据结构
typedef struct EdgeNode
{
	int adjvex;
	int weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode{
	int in;
	int data;
	EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

typedef struct 
{
	AdjList adjList;
	int numVertexes,numEdges;
}graphAdjList,*GraphAdjList;
//拓扑排序，若GL无回路，则输出拓扑排序序列并返回OK，若有回路返回ERROR
Status TopologicalSort(GraphAdjList GL){
	EdgeNode *e;
	int i,k,gettop;
	int top = 0;
	int count = 0;
	int *stack;
	stack = (int *)malloc(GL->numVertexes*sizeof(int));
	for(i=0;i<GL->numVertexes;i++)
		if(GL->adjList[i].in == 0)
			stack[++top] = i;
	while(top!=0){
		gettop = stack[top--];
		printf("%d -> ",GL->adjList[gettop].data );
		count++;
		for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top] = k;
		}
	}
	if(count<GL->numVertexes)
		return ERROR;
	else
		return OK;
}


//关键路径算法
int *etv,*ltv;
int *stack2;
int top2;
//拓扑排序，用于关键路径计算
Status TopologicalSort(GraphAdjList GL){
	EdgeNode *e;
	int i,k,gettop;
	int top = 0;
	int count =0;
	int *stack;
	stack = (int *)malloc(GL->numVertexes*sizefo(int));
	for(i=0;i<GL->numVertexes;i++)
		if(0==GL->adjList[i].in)
			stack[++top]=i;
	top2 = 0;
	etv = (int *)malloc(GL->numVertexes*sizeof(int));

	for(i=0;i<numVertexes;i++)
		etv[i]==0;
	stack2 = (int *) malloc(GL->numVertexes*sizeof(int));
	while(top!=0){
		gettop = stack[top--];
		count++;
		stack2[++top]=gettop;
		for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top] = k;
			if((etv[gettop]+e->weight)>etv[k])
				etv[k] = etv[gettop]+e->weight;
		}
	}
	if(count<GL->numVertexes)
		return ERROR;
	else
		return OK;
}
//求关键路径，GL为有向网，输出GL的各项关键活动
void CriticalPath(GraphAdjList GL){
	EdgeNode *e;
	int i,gettop,k,j;
	int ete,lte;
	TopologicalSort(GL);
	ltv = (int *)malloc(GL->numVertexes*sizeof(int));
	for(i=0;i<GL->numVertexes;i++)
		ltv[i] = etv[GL->numVertexes-1];
	while(top2!=0){
		gettop = stack2[top2--];
		for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			if(ltv[k]->e->weight<lv[gettop]){
				ltv[gettop] = ltv[k]-e->weight;
			}
		}
	}
	for(j=0;j<GL->numVertexes;j++){
		for(e=GL->adjList[j].firstedge;e;e=e->next){
			k=e->adjvex;
			ete=etv[j];
			lte = ltv[k]-e->weight;
			if(ete==lte)
				printf("<v%d,v%d> length: %d",GL->adjList[j].data,GL->adjList[k].data,e->weight );
		}
	}
}







