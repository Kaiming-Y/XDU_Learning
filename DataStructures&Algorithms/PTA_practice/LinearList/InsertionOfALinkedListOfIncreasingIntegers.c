/*
 *[函数题] 递增的整数序列链表的插入
 * 本题要求实现一个函数，在递增的整数序列链表（带头结点）中插入一个新整数，并保持该序列的有序性。
 * 函数接口定义：
 *     List Insert( List L, ElementType X );
 * 其中List结构定义如下：
 *     typedef struct Node *PtrToNode;
 *     struct Node {
 *     ElementType Data;  存储结点数据
 *     PtrToNode   Next;  指向下一个结点的指针
 *     };
 *     typedef PtrToNode List; 定义单链表类型
 * L是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Insert要将X插入L，并保持该序列的有序性，返回插入后的链表头指针。
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

List Insert( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    L = Read();
    scanf("%d", &X);
    L = Insert(L, X);
    Print(L);
    return 0;
}

List Insert( List L, ElementType X ){
    List p, s;
    p = L;
    s = (List) malloc(sizeof (struct Node));
    s->Data = X;
    s->Next = NULL;
    while(p->Next != NULL && p->Next->Data < X) p = p->Next;
    s->Next = p->Next;
    p->Next = s;
    return L;
}