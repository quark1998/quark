#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
//����ѭ������
#define MAXQSIZE 1024
//˳����е��������
typedef int QElemType;//���������Ԫ�����ͣ��ɵ���
typedef struct {
        QElemType data[MAXQSIZE];//���ݵĴ洢��
		int front,rear;//��ͷ����βָ��
		int num;//����Ԫ�صĸ���
}c_SeqQ;//ѭ����
#define MaxVerNum 100//��󶥵���Ϊ100
#define MaxInt 32767  //��ʾ����ֵ����oo
//�����ڽӾ�����������
typedef char VertexType;//����������Ϊ�ַ���
typedef int ArcType;//�ߵ�Ȩֵ��Ϊ����
typedef int OtheInfo;//�����������Ϣ������Ȩֵ
typedef struct {
     VertexType vexs[MaxVerNum];//������洢������Ϣ
	 ArcType arcs[MaxVerNum][MaxVerNum];//�ڽӾ��󣬼��߱�
	 int vexnum, arcnum;//�������ͱ���
}AMGraph;//AMGraph�����ڽӾ���洢��ͼ����
//�����ڽӱ���������
typedef struct ArcNode {//�߽��
int adjvex;//�ñ���ָ��Ķ����λ��
struct ArcNode *nextarc;//ָ����һ���ߵ�ָ��
OtheInfo info;//��Ҫ��ʾ������Ϣ�������Ӹ�������
}ArcNode;
typedef struct VNode{//�������
VertexType data;//������Ϣ
ArcNode *firstarc;//ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[MaxVerNum]; //AdjList��ʾ�ڽӱ�����
typedef struct {
     AdjList vertices;//�ڽӱ�
	 int vexnum, arcnum;//ͼ�Ķ������ͱ���
}ALGraph;//ALGraph�����ڽӱ�ʽ�洢��ͼ����
//ѭ�����еĳ�ʼ��
int InitQueue_Sq(c_SeqQ*&Q)
{
if( !(Q = new c_SeqQ))//�洢����ʧ��
return ERROR;
Q->front=Q->rear=0;
Q->num=0;
return OK;
}
//����˳�����
int DestroyQueue_Sq(c_SeqQ *Q)
{
    if (!Q){
	delete Q;
	return OK;
	}
	return ERROR;
}
//�ж�˳����п�
int QueueEmpty_Sq(c_SeqQ *Q)
{
return (Q->num==0) ;
}
//��Ӳ���
int EnQueue_Sq(c_SeqQ *Q , QElemType e)
{
     if (Q->num==MAXQSIZE) return ERROR;//���������
	 Q->data[Q->rear]=e;//Ԫ�����
	 Q->rear=(Q->rear+1)%MAXQSIZE;//�޸Ķ�βָ��ֵ
	 Q->num++;
	 return OK;
}
//���Ӳ���
int DeQueue_Sq (c_SeqQ *Q , QElemType &e)
{
     if(Q->num==0) return ERROR;//�ӿ�
	 e=Q->data[Q->front];//������ͷԪ��
	 Q->front=(Q->front+1)% MAXQSIZE;//�޸Ķ���ָ��ֵ
	 Q->num--;
	 return OK;
}
//����ͼG���ڽӾ���洢
void CreateAMGraph(AMGraph &G)
{
     int i,j,k;
	 int flag=1;//��־�����flag=1����ʾ����ͼ�����򣬱�ʾ����ͼ
	 printf("ͼΪ����ͼ����������ͼ������1����ʾ����ͼ�����򣬱�ʾ����ͼ:");
	 scanf("%d", &flag);
	 printf("�����붥�����ͱ���(�����ʽΪ:������,����): ");
	 scanf("%d,%d",&G.vexnum, &G.arcnum);//���붥�����ͱ���
	 printf("�����붥����Ϣ(����:����5�����㣬����������ABCDE): ");
	 _flushall();
	 for (i=0; i<G.vexnum; i++)
	 scanf("%c",&G.vexs[i]);//���붥����Ϣ�����������
	 for (i=0;i<G.vexnum; i++)
	     for (j=0;j<G.vexnum ;j++)
             G.arcs[i][j]=0;//��ʼ���ڽӾ���
	 printf("ע��:�������ж�Ӧ����Ŵӧ���ʼ��ţ���0��1��2��.....n");
	 printf("������ÿ���߶�Ӧ��������������(�����ʽΪ:i,j<cr>):\n");
	 for (k=0;k< G.arcnum; k++){
	 for ( i=0; i<G.vexnum;i++)
	 printf("%c--%d\n",G.vexs[i],i);
	 printf("\n");
	 printf("�������%d����: ",k+1);
	 scanf("\n%d,%d",&i,&j);//����e���ߣ������ڽӾ���
	 if (i<0 || i>=G.vexnum ||j<0 ||j>=G.vexnum){
	 printf("�������! \n");
	 k--;
	 continue;
	 }
	 printf("(%c--%c)\n",G.vexs[i], G.vexs[j]);
	 G.arcs[i][j]=1;
	 if (flag==1)
	 G.arcs[j][i]=1;//����ͼ���ڽӾ���洢����
   }
}
//����ͼ���ڽӱ�洢
void CreateALGraph(ALGraph &G)
{
     int i,j,k;
	 ArcNode *s;
	 int flag=1;//��־�����flag=1����ʾ����ͼ�����򣬱�ʾ����ͼ
	 printf("ͼΪ����ͼ����������ͼ������1����ʾ����ͼ�����򣬱�ʾ����ͼ: ");
	 scanf("%d", &flag);
	 printf("�����붥�����ͱ���(�����ʽΪ:������,����): ");
	 scanf("%d,%d",&G.vexnum,&G.arcnum);//���붥�����ͱ���
	 printf("�����붥����Ϣ(����:����5�����㣬����������ABCDE): ");
	 _flushall();
	 for (i=0;i<G.vexnum;i++){//������n������Ķ����
          scanf("%c",&G.vertices[i].data);//���붥����Ϣ
          G.vertices[i].firstarc=NULL;//����ı߱�ͷָ����Ϊ��
}
     printf("ע��:�������ж�Ӧ����Ŵӧ���ʼ��ţ���0��1��2��.....n)");
	 printf("������ÿ���߶�Ӧ��������������(�����ʽΪ:ij<cr>): \n");
	 for (k=0; k<G.arcnum; k++){//�����߱�
	 for (i=0; i<G.vexnum;i++)
	 printf("%c--%dn",G.vertices[i].data,i);
	 printf("'\n");
	 printf("�������%d����: ",k+1);
	 scanf("\n%d,%d",&i,&j);//�����(Vi,Vj)��<Vi,Vj>�Ķ����Ӧ���
	 if (i<0 || i>=G.vexnum ||j<0||j>=G.vexnum){
	 printf("�������! \n");
	 k--;
	 continue;
     }
     printf("(%c--%c)\n",G.vertices[i].data,G.vertices[j].data);
	 s=new ArcNode;//�����±߱���s
	 s->adjvex=j;//�ڽӵ����Ϊj
	 s->nextarc=G.vertices[i].firstarc;//���±߱���s���뵽����Vi�ı߱�ͷ��G.vertices[i].firstarc=s;
	 if (flag==1){//����ͼ
	 s=new ArcNode;//�����±߱���s
	 s->adjvex=i;//�ڽӵ����Ϊi
	 s->nextarc=G.vertices[j].firstarc;//���±߱���s���뵽����Vj�ı߱�ͷ��
	 G.vertices[j].firstarc=s;
     }
   }
}
//���������������һ����ͨͼ(ͼ�Ĵ洢�ṹ�����ڽӾ����ʾ)
//�ӵ�v����������ݹ��������ȱ���ͼG��ͼ�Ĵ洢�ṹ�����ڽӾ����ʾ��
//��1���β�AMGraph G��ָҪ������ͼ�Ĵ洢�ṹ
//��2���β�int v��ָ�����Ϊv�Ķ��㿪ʼ������ȱ���ͼ
//��3���β�int visited[]���飬ָʾ�����Ƿ񱻷��ʹ�
void DFSM(AMGraph G, int v, int visited[])
{
     visited[v]=1;//���÷��ʱ�־������Ӧ����ֵΪ1
	 printf("���ʵĶ�����:%d ----%c\n", v, G.vexs[v]);//��������ʵĶ���
	 for (int w=0; w<G.vexnum; w++)//���μ���ڽӾ���v���ڵ���
	 if ((G.arcs[v][w]!=0)&&(!visited[w])) //G.arcs[v][w]!=0��ʾw��v���ڽӶ��㣬
	 DFSM(G,w,visited);//���wδ���ʣ���ݹ����DFS
}
//������ȱ���ͼ(ͼ�Ĵ洢�ṹ�����ڽӾ����ʾ)
void DFSMTraverse(AMGraph &G)
{
     int v, visited[MaxVerNum];
	 for ( v=0; v<G.vexnum;++v)//��ʼ�� visited����,������ÿһ��Ԫ�ض�Ӧͼ��
	      visited[v]=0;//һ������,������ʶ�����Ƿ񱻷��ʹ�
	 for (v=0; v<G.vexnum; ++v){
	      if (!visited[v]){
		  printf("�Ӷ���%c��ʼ����������ȱ���\n",G.vexs[v]);
		  DFSM(G, v, visited);//��δ���ʹ��Ķ������DFS
      }
   }
}
//�������������������(ͼ�Ĵ洢�ṹ�����ڽӱ��ʾ)
//��1���β�ALGraph &G��ָҪ������ͼ�Ĵ洢�ṹ
//��2���β�int v��ָ�����Ϊv�Ķ��㿪ʼ������ȱ���ͼ
//��3���β�int visited���飬ָʾ�����Ƿ񱻷��ʹ�
void BFSL(ALGraph &G,int v,int visited[])
{
     c_SeqQ *queue;//����һ��˳�����
	 InitQueue_Sq(queue);//��ʼ������
	 ArcNode*p;//�����ָ��
	 visited[v]=1;//��ʶ���Ϊv�Ķ��㱻���ʹ�
	 printf("���ڷ��ʵĶ�����:%d --- %c\n",v, G.vertices[v].data);//��������ʵĶ���
	 if (EnQueue_Sq(queue,v)==0 ){//�ѷ��ʹ��ĵ���������
	     printf("��������������󣬽���! \n");
		 exit(1);//�����������
     }
     while (!QueueEmpty_Sq(queue)){//���в���
	     DeQueue_Sq(queue, v);
	     p=G.vertices[v].firstarc;
		 while(p){
		     if(visited[p->adjvex]==0){//�ж�p->adjvex �����Ƿ񱻷��ʹ�
			 visited[p->adjvex]=1;//��û�����ʹ����������з���
			 printf("���ʵĶ�����:%d ---%c\n", p->adjvex,
                  G.vertices[p->adjvex].data);//��������ʵĽ��
             if (EnQueue_Sq(queue,p->adjvex) ==0 ){//�ѷ��ʹ��ĵ���������
			      printf("��������������󣬽���! \n");
                  exit(1);//�����������
             }
        }
        p=p->nextarc;//ָ����һ�����ڶ���
     }
  }  
  DestroyQueue_Sq(queue);//ɾ������
}
//������ȱ���ͼ(ͼ�Ĵ洢�ṹ�����ڽӱ��ʾ)
void BFSLTraverse(ALGraph &G)
{
      int v, visited[MaxVerNum];
	  for (v=0; v<G.vexnum; v++)//��ʼ�� visited����,������ÿһ��Ԫ�ض�Ӧͼ��
	       visited[v]=0;//һ������,������ʶ�����Ƿ񱻷��ʹ�
      for (v=0; v<G.vexnum; v++){
           if (!visited[v]){
           printf("�Ӷ���%c��ʼ���й��������������\n", G.vertices[v].data);
		   BFSL(G,v,visited);// vδ���ʹ�����v��ʼBFS ����
           }  
      }
}
void showmenu()
{
	  printf("                  --ͼ�ı���--                  \n");
	  printf("************************************************\n");
	  printf("*       1-------���ڽӾ�����ʾһ��ͼ         *\n");
	  printf("*       2-------���ڽӱ��ʾһ��ͼ             *\n");
	  printf("*       3-------���������������ͼ(�ڽӾ����) *\n");
	  printf("*       4-------���������������ͼ(�ڽӱ�)     *\n");
	  printf("*       5-------���������������ͼ(�ڽӾ����) *\n");
	  printf("*       6-------���������������ͼ(�ڽӱ�)     *\n");
	  printf("*       O-------�˳�                           *\n");
	  printf("***********************************************\n ");
	  printf("��ѡ��˵���(0--6): ");
}

void graphOP()
{
      char choice='N';
	  int adjacency_matrix = 0; //��־�ڽӾ����Ƿ����
	  int adjacency_list = 0;//��־�ڽӱ��Ƿ����
	  AMGraph G;//�ڽӾ���
	  ALGraph T;//�ڽӱ�
	  while(choice!='0')
	  {
	  showmenu();
	  _flushall();
	  scanf("%c",&choice);
	  switch(choice)
	  {
	  case '1':
	  CreateAMGraph(G);//����ͼ���ڽӾ���
	      adjacency_matrix = 1;
	  break;
	  case '2':
	  CreateALGraph(T);//����ͼ���ڽӱ�
	      adjacency_list= 1;
	  break;
	  case '3'://���������������ͼ���ڽӾ����)
	  if (adjacency_matrix) {
	      DFSMTraverse(G);} 
	  else {
	  printf("��������ͼ�Ķ�����Ϣ! \n");
	  }
	  break;
	  case '4'://���������������ͼ(�ڽӱ�)
	  if (adjacency_list) {
	      DFSMTraverse(G);
	  }else {
	  printf("��������ͼ�Ķ�����Ϣ!\n");
	  }
	  break;
	  case '5'://���������������ͼ���ڽӾ����)
	  if (adjacency_matrix){
	      BFSLTraverse(T);
      }else {
	  printf("��������ͼ�Ķ�����Ϣ! \n");
	  }
	  break;
	  case '6'://���������������ͼ���ڽӱ�)
	  if (adjacency_list){
	      BFSLTraverse(T);} 
	  else {
	  printf("��������ͼ�Ķ�����Ϣ! \n");
	  }
	  break;
	  case '0':
	  printf("\n\t�������! \n");
	  break;
	  default:
	  printf("\n\t�����������������! \n");
	  }
   }
}
int main()
{
      graphOP();
      return 0;
}

