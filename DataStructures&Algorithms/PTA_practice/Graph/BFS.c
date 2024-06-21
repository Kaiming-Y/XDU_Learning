/*
 * [函数题] 邻接表存储图的广度优先遍历
 * 试实现邻接表存储图的广度优先遍历。
 * 函数BFS应从第S个顶点出发对邻接表存储的图Graph进行广度优先搜索，遍历时用裁判定义的函数Visit访问每个顶点。当访问邻接点时，要求按邻接表顺序访问。题目保证S是图中的合法顶点。
 */

#include <stdio.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10   /* 最大顶点数设为10 */
typedef int Vertex;       /* 用顶点下标表示顶点,为整型 */

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
} AdjList[MaxVertexNum];     /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

bool Visited[MaxVertexNum]; /* 顶点的访问标记 */

LGraph CreateGraph(); /* 创建图并且将Visited初始化为false；裁判实现，细节不表 */

void Visit( Vertex V )
{
    printf(" %d", V);
}

void BFS ( LGraph Graph, Vertex S, void (*Visit)(Vertex) );

int main()
{
    LGraph G;
    Vertex S;

    G = CreateGraph();
    scanf("%d", &S);
    printf("BFS from %d:", S);
    BFS(G, S, Visit);

    return 0;
}

void BFS ( LGraph Graph, Vertex S, void (*Visit)(Vertex) ) {
    Vertex queue[MaxVertexNum];
    int front = 0, rear = front;
    queue[rear++] = S;
    Visited[S] = true;
    PtrToAdjVNode p;
    while(front < rear){
        Vertex v = queue[front++];
        Visit(v);
        p = Graph->G[v].FirstEdge;
        while (p) {
            if (!Visited[p->AdjV]) {
                queue[rear++] = p->AdjV;
                Visited[p->AdjV] = true;
            }
            p = p->Next;
        }
    }
}