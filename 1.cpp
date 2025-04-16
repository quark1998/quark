#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
//定义循环队列
#define MAXQSIZE 1024
//顺序队列的最大容量
typedef int QElemType;//定义队列中元素类型，可调整
typedef struct {
        QElemType data[MAXQSIZE];//数据的存储区
		int front,rear;//队头、队尾指针
		int num;//队中元素的个数
}c_SeqQ;//循环队
#define MaxVerNum 100//最大顶点数为100
#define MaxInt 32767  //表示极大值，即oo
//定义邻接矩阵数据类型
typedef char VertexType;//顶点类型设为字符型
typedef int ArcType;//边的权值设为整型
typedef int OtheInfo;//顶点的其他信息，比如权值
typedef struct {
     VertexType vexs[MaxVerNum];//顶点表，存储顶点信息
	 ArcType arcs[MaxVerNum][MaxVerNum];//邻接矩阵，即边表
	 int vexnum, arcnum;//顶点数和边数
}AMGraph;//AMGraph是以邻接矩阵存储的图类型
//定义邻接表数据类型
typedef struct ArcNode {//边结点
int adjvex;//该边所指向的顶点的位置
struct ArcNode *nextarc;//指向下一条边的指针
OtheInfo info;//若要表示边上信息，则增加该数据域
}ArcNode;
typedef struct VNode{//顶点表结点
VertexType data;//顶点信息
ArcNode *firstarc;//指向第一条依附该顶点的边的指针
}VNode, AdjList[MaxVerNum]; //AdjList表示邻接表类型
typedef struct {
     AdjList vertices;//邻接表
	 int vexnum, arcnum;//图的顶点数和边数
}ALGraph;//ALGraph是以邻接表方式存储的图类型
//循环队列的初始化
int InitQueue_Sq(c_SeqQ*&Q)
{
if( !(Q = new c_SeqQ))//存储分配失败
return ERROR;
Q->front=Q->rear=0;
Q->num=0;
return OK;
}
//销毁顺序队列
int DestroyQueue_Sq(c_SeqQ *Q)
{
    if (!Q){
	delete Q;
	return OK;
	}
	return ERROR;
}
//判断顺序队列空
int QueueEmpty_Sq(c_SeqQ *Q)
{
return (Q->num==0) ;
}
//入队操作
int EnQueue_Sq(c_SeqQ *Q , QElemType e)
{
     if (Q->num==MAXQSIZE) return ERROR;//队满，溢出
	 Q->data[Q->rear]=e;//元素入队
	 Q->rear=(Q->rear+1)%MAXQSIZE;//修改队尾指针值
	 Q->num++;
	 return OK;
}
//出队操作
int DeQueue_Sq (c_SeqQ *Q , QElemType &e)
{
     if(Q->num==0) return ERROR;//队空
	 e=Q->data[Q->front];//读出队头元素
	 Q->front=(Q->front+1)% MAXQSIZE;//修改队首指针值
	 Q->num--;
	 return OK;
}
//建立图G的邻接矩阵存储
void CreateAMGraph(AMGraph &G)
{
     int i,j,k;
	 int flag=1;//标志，如果flag=1，表示无向图，否则，表示有向图
	 printf("图为有向图，还是无向图，输入1，表示无向图，否则，表示有向图:");
	 scanf("%d", &flag);
	 printf("请输入顶点数和边数(输入格式为:顶点数,边数): ");
	 scanf("%d,%d",&G.vexnum, &G.arcnum);//输入顶点数和边数
	 printf("请输入顶点信息(例如:若有5个顶点，则连续输入ABCDE): ");
	 _flushall();
	 for (i=0; i<G.vexnum; i++)
	 scanf("%c",&G.vexs[i]);//输入顶点信息，建立顶点表
	 for (i=0;i<G.vexnum; i++)
	     for (j=0;j<G.vexnum ;j++)
             G.arcs[i][j]=0;//初始化邻接矩阵
	 printf("注意:顶点序列对应的序号从О起始编号，即0，1，2，.....n");
	 printf("请输入每条边对应的两个顶点的序号(输入格式为:i,j<cr>):\n");
	 for (k=0;k< G.arcnum; k++){
	 for ( i=0; i<G.vexnum;i++)
	 printf("%c--%d\n",G.vexs[i],i);
	 printf("\n");
	 printf("请输入第%d条边: ",k+1);
	 scanf("\n%d,%d",&i,&j);//输入e条边，建立邻接矩阵
	 if (i<0 || i>=G.vexnum ||j<0 ||j>=G.vexnum){
	 printf("输入出错! \n");
	 k--;
	 continue;
	 }
	 printf("(%c--%c)\n",G.vexs[i], G.vexs[j]);
	 G.arcs[i][j]=1;
	 if (flag==1)
	 G.arcs[j][i]=1;//无向图的邻接矩阵存储建立
   }
}
//建立图的邻接表存储
void CreateALGraph(ALGraph &G)
{
     int i,j,k;
	 ArcNode *s;
	 int flag=1;//标志，如果flag=1，表示无向图，否则，表示有向图
	 printf("图为有向图，还是无向图，输入1，表示无向图，否则，表示有向图: ");
	 scanf("%d", &flag);
	 printf("请输入顶点数和边数(输入格式为:顶点数,边数): ");
	 scanf("%d,%d",&G.vexnum,&G.arcnum);//读入顶点数和边数
	 printf("请输入顶点信息(例如:若有5个顶点，则连续输入ABCDE): ");
	 _flushall();
	 for (i=0;i<G.vexnum;i++){//建立有n个顶点的顶点表
          scanf("%c",&G.vertices[i].data);//读入顶点信息
          G.vertices[i].firstarc=NULL;//顶点的边表头指针设为空
}
     printf("注意:顶点序列对应的序号从О起始编号，即0，1，2，.....n)");
	 printf("请输入每条边对应的两个顶点的序号(输入格式为:ij<cr>): \n");
	 for (k=0; k<G.arcnum; k++){//建立边表
	 for (i=0; i<G.vexnum;i++)
	 printf("%c--%dn",G.vertices[i].data,i);
	 printf("'\n");
	 printf("请输入第%d条边: ",k+1);
	 scanf("\n%d,%d",&i,&j);//读入边(Vi,Vj)或<Vi,Vj>的顶点对应序号
	 if (i<0 || i>=G.vexnum ||j<0||j>=G.vexnum){
	 printf("输入出错! \n");
	 k--;
	 continue;
     }
     printf("(%c--%c)\n",G.vertices[i].data,G.vertices[j].data);
	 s=new ArcNode;//生成新边表结点s
	 s->adjvex=j;//邻接点序号为j
	 s->nextarc=G.vertices[i].firstarc;//将新边表结点s插入到顶点Vi的边表头部G.vertices[i].firstarc=s;
	 if (flag==1){//无向图
	 s=new ArcNode;//生成新边表结点s
	 s->adjvex=i;//邻接点序号为i
	 s->nextarc=G.vertices[j].firstarc;//将新边表结点s插入到顶点Vj的边表头部
	 G.vertices[j].firstarc=s;
     }
   }
}
//深度优先搜索遍历一个连通图(图的存储结构采用邻接矩阵表示)
//从第v个顶点出发递归地深度优先遍历图G，图的存储结构采用邻接矩阵表示。
//第1个形参AMGraph G是指要遍历的图的存储结构
//第2个形参int v是指从序号为v的顶点开始深度优先遍历图
//第3个形参int visited[]数组，指示顶点是否被访问过
void DFSM(AMGraph G, int v, int visited[])
{
     visited[v]=1;//设置访问标志数组相应分量值为1
	 printf("访问的顶点是:%d ----%c\n", v, G.vexs[v]);//输出正访问的顶点
	 for (int w=0; w<G.vexnum; w++)//依次检查邻接矩阵v所在的行
	 if ((G.arcs[v][w]!=0)&&(!visited[w])) //G.arcs[v][w]!=0表示w是v的邻接顶点，
	 DFSM(G,w,visited);//如果w未访问，则递归调用DFS
}
//深度优先遍历图(图的存储结构采用邻接矩阵表示)
void DFSMTraverse(AMGraph &G)
{
     int v, visited[MaxVerNum];
	 for ( v=0; v<G.vexnum;++v)//初始化 visited数组,该数组每一个元素对应图的
	      visited[v]=0;//一个顶点,用来标识顶点是否被访问过
	 for (v=0; v<G.vexnum; ++v){
	      if (!visited[v]){
		  printf("从顶点%c开始进行深度优先遍历\n",G.vexs[v]);
		  DFSM(G, v, visited);//对未访问过的顶点调用DFS
      }
   }
}
//广度优先搜索遍历函数(图的存储结构采用邻接表表示)
//第1个形参ALGraph &G是指要遍历的图的存储结构
//第2个形参int v是指从序号为v的顶点开始广度优先遍历图
//第3个形参int visited数组，指示顶点是否被访问过
void BFSL(ALGraph &G,int v,int visited[])
{
     c_SeqQ *queue;//定义一个顺序队列
	 InitQueue_Sq(queue);//初始化队列
	 ArcNode*p;//定义边指针
	 visited[v]=1;//标识序号为v的顶点被访问过
	 printf("现在访问的顶点是:%d --- %c\n",v, G.vertices[v].data);//输出正访问的顶点
	 if (EnQueue_Sq(queue,v)==0 ){//把访问过的点放入队列中
	     printf("队溢出，操作错误，结束! \n");
		 exit(1);//队列满，溢出
     }
     while (!QueueEmpty_Sq(queue)){//队列不空
	     DeQueue_Sq(queue, v);
	     p=G.vertices[v].firstarc;
		 while(p){
		     if(visited[p->adjvex]==0){//判断p->adjvex 顶点是否被访问过
			 visited[p->adjvex]=1;//若没被访问过，则对其进行访问
			 printf("访问的顶点是:%d ---%c\n", p->adjvex,
                  G.vertices[p->adjvex].data);//输出正访问的结点
             if (EnQueue_Sq(queue,p->adjvex) ==0 ){//把访问过的点放入队列中
			      printf("队溢出，操作错误，结束! \n");
                  exit(1);//队列满，溢出
             }
        }
        p=p->nextarc;//指向下一个相邻顶点
     }
  }  
  DestroyQueue_Sq(queue);//删除队列
}
//广度优先遍历图(图的存储结构采用邻接表表示)
void BFSLTraverse(ALGraph &G)
{
      int v, visited[MaxVerNum];
	  for (v=0; v<G.vexnum; v++)//初始化 visited数组,该数组每一个元素对应图的
	       visited[v]=0;//一个顶点,用来标识顶点是否被访问过
      for (v=0; v<G.vexnum; v++){
           if (!visited[v]){
           printf("从顶点%c开始进行广度优先搜索遍历\n", G.vertices[v].data);
		   BFSL(G,v,visited);// v未访问过，从v开始BFS 搜索
           }  
      }
}
void showmenu()
{
	  printf("                  --图的遍历--                  \n");
	  printf("************************************************\n");
	  printf("*       1-------用邻接矩阵表表示一个图         *\n");
	  printf("*       2-------用邻接表表示一个图             *\n");
	  printf("*       3-------深度优先搜索遍历图(邻接矩阵表) *\n");
	  printf("*       4-------深度优先搜索遍历图(邻接表)     *\n");
	  printf("*       5-------广度优先搜索遍历图(邻接矩阵表) *\n");
	  printf("*       6-------广度优先搜索遍历图(邻接表)     *\n");
	  printf("*       O-------退出                           *\n");
	  printf("***********************************************\n ");
	  printf("请选择菜单号(0--6): ");
}

void graphOP()
{
      char choice='N';
	  int adjacency_matrix = 0; //标志邻接矩阵是否存在
	  int adjacency_list = 0;//标志邻接表是否存在
	  AMGraph G;//邻接矩阵
	  ALGraph T;//邻接表
	  while(choice!='0')
	  {
	  showmenu();
	  _flushall();
	  scanf("%c",&choice);
	  switch(choice)
	  {
	  case '1':
	  CreateAMGraph(G);//创建图的邻接矩阵
	      adjacency_matrix = 1;
	  break;
	  case '2':
	  CreateALGraph(T);//创建图的邻接表
	      adjacency_list= 1;
	  break;
	  case '3'://深度优先搜索遍历图（邻接矩阵表)
	  if (adjacency_matrix) {
	      DFSMTraverse(G);} 
	  else {
	  printf("请先输入图的顶点信息! \n");
	  }
	  break;
	  case '4'://深度优先搜索遍历图(邻接表)
	  if (adjacency_list) {
	      DFSMTraverse(G);
	  }else {
	  printf("请先输入图的顶点信息!\n");
	  }
	  break;
	  case '5'://广度优先搜索遍历图（邻接矩阵表)
	  if (adjacency_matrix){
	      BFSLTraverse(T);
      }else {
	  printf("请先输入图的顶点信息! \n");
	  }
	  break;
	  case '6'://广度优先搜索遍历图（邻接表)
	  if (adjacency_list){
	      BFSLTraverse(T);} 
	  else {
	  printf("请先输入图的顶点信息! \n");
	  }
	  break;
	  case '0':
	  printf("\n\t程序结束! \n");
	  break;
	  default:
	  printf("\n\t输入错误，请重新输入! \n");
	  }
   }
}
int main()
{
      graphOP();
      return 0;
}

