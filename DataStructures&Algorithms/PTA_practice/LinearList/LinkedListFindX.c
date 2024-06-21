/*
 * [函数题] 链式表的按序号查找
 * 本题要求实现一个函数，找到并返回链式表的第K个元素。
 * 函数接口定义：
 *  ElementType FindKth( List L, int K );
 * 其中List结构定义如下：
 *  typedef struct LNode *PtrToLNode;
 *  struct LNode {
 *  ElementType Data;
 *  PtrToLNode Next;
 *  };
 *  typedef PtrToLNode List;
 * L是给定单链表，函数FindKth要返回链式表的第K个元素。如果该元素不存在，则返回ERROR。
 */
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

List Read(); /* 细节在此不表 */

ElementType FindKth( List L, int K );

int main()
{
    int N, K;
    ElementType X;
    List L = Read();
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &K);
        X = FindKth(L, K);
        if ( X!= ERROR )
            printf("%d ", X);
        else
            printf("NA ");
    }
    return 0;
}

ElementType FindKth( List L, int K ){
    List p = L;
    int i = 1;
    while(p!=NULL && i<K){
        p = p->Next;
        i++;
    }
    if(p != NULL && i == K) return p->Data; //***p != NULL  这个判定很重要, 避免出现K过大, 根本不在链表范围内的情况
    else return ERROR;
}