/*
 * [函数题] 二叉树的遍历
 * 本题要求给定二叉树的4种遍历。
 * 要求4个函数分别按照访问顺序打印出结点的内容，格式为一个空格跟着一个字符。
 * ##输出样例:
 *  Inorder: D B E F A G H C I
 *  Preorder: A B D F E C G H I
 *  Postorder: D E F B H G I C A
 *  Levelorder: A B C D F G I E H
 */

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

typedef struct LNode* Node;
struct LNode{
    BinTree Data;
    Node Next;
};
typedef struct QNode* Queue;
struct QNode{
    struct LNode* front;
    struct LNode* rear;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );
Queue CreateQueue();
void AddQ(BinTree Element, Queue Q);
BinTree DeleteQ(Queue Q);
int isEmpty(Queue Q);

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}

void InorderTraversal( BinTree BT ){
    if ( BT ) {
        InorderTraversal(BT->Left);
        printf("%c", BT->Data);
        InorderTraversal(BT->Right);
    }
}

void PreorderTraversal( BinTree BT ){
    if ( BT ) {
        printf("%c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void PostorderTraversal( BinTree BT ){
    if ( BT ) {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf("%c", BT->Data);
    }
}

void LevelorderTraversal( BinTree BT ){
    Queue Q;
    BinTree B;
    if ( !BT ) return;
    Q = CreateQueue();
    AddQ(BT, Q);
    while ( !isEmpty(Q) ) {
        B = DeleteQ(Q);
        printf("%c", B->Data);
        if ( B->Left ) AddQ(B->Left, Q);
        if ( B->Right ) AddQ(B->Right, Q);
    }
}

Queue CreateQueue(){
    Queue Q;
    Node Headnode;
    Q = (Queue) malloc(sizeof (struct QNode));
    Headnode = (Node) malloc(sizeof (struct LNode));
    Headnode->Next = NULL;
    Q->front = Headnode;
    Q->rear = Q->front;
    return Q;
}

void AddQ(BinTree Element, Queue Q){
    Node t = (Node) malloc(sizeof (struct LNode));
    t->Data = Element;
    t->Next = NULL;
    Q->rear->Next = t;
    Q->rear = t;
}

BinTree DeleteQ(Queue Q){
    if ( isEmpty(Q) ) return NULL;
    BinTree Element;
    Node t;
    t = Q->front->Next;
    Element = t->Data;
    Q->front->Next = t->Next;
    if ( Q->rear == t ) {
        Q->rear = Q->front;
    }
    free(t);
    return Element;
}

int isEmpty(Queue Q){
    return ( Q->front == Q->rear ) ;
}