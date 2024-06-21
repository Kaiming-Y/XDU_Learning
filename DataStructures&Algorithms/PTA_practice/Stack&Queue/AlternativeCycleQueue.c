/*
 * [函数题]
 * 如果用一个循环数组表示队列，并且只设队列头指针Front，不设尾指针Rear，而是另设Count记录队列中元素个数。请编写算法实现队列的入队和出队操作。
 * 函数接口定义：
 *  bool AddQ( Queue Q, ElementType X );
 *  ElementType DeleteQ( Queue Q );
 * 其中Queue结构定义如下：
 * typedef int Position;
 * typedef struct QNode *PtrToQNode;
 * struct QNode {
 *  ElementType *Data;   存储元素的数组
 *  Position Front;      队列的头指针
 *  int Count;           队列中元素个数
 *  int MaxSize;         队列最大容量
 * };
 * typedef PtrToQNode Queue;
 * 注意：如果队列已满，AddQ函数必须输出“Queue Full”并且返回false；如果队列是空的，则DeleteQ函数必须输出“Queue Empty”，并且返回ERROR。
 * 输入样例：
 * 4
 * Del
 * Add 5
 * Add 4
 * Add 3
 * Del
 * Del
 * Add 2
 * Add 1
 * Add 0
 * Add 10
 * End
 * 输出样例：
 * Queue Empty
 * 5 is out
 * 4 is out
 * Queue Full
 * 3 2 1 0
*/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef enum { addq, delq, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode {
    ElementType *Data;  /* 存储元素的数组   */
    Position Front;     /* 队列的头、尾指针 */
    int Count;          /* 队列中元素个数   */
    int MaxSize;        /* 队列最大容量     */
};
typedef PtrToQNode Queue;

Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = 0;
    Q->Count = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool AddQ( Queue Q, ElementType X );
ElementType DeleteQ( Queue Q );

Operation GetOp();  /* 裁判实现，细节不表 */

int main()
{
    ElementType X;
    Queue Q;
    int N, done = 0;

    scanf("%d", &N);
    Q = CreateQueue(N);
    while ( !done ) {
        switch( GetOp() ) {
            case addq:
                scanf("%d", &X);
                AddQ(Q, X);
                break;
            case delq:
                X = DeleteQ(Q);
                if ( X!=ERROR ) printf("%d is out\n", X);
                break;
            case end:
                while (Q->Count) printf("%d ", DeleteQ(Q));
                done = 1;
                break;
        }
    }
    return 0;
}

bool AddQ( Queue Q, ElementType X ){
    if (Q->Count == Q->MaxSize) {
        printf("Queue Full\n");
        return false;
    }
    Q->Data[(Q->Front+Q->Count)%Q->MaxSize] = X;
    Q->Count++;
    return true;
}

ElementType DeleteQ( Queue Q ){
    if(Q->Count == 0) {
        printf("Queue Empty\n");
        return ERROR;
    }
    Q->Count--;
    ElementType data = Q->Data[Q->Front];
    Q->Front = (Q->Front + 1) % Q->MaxSize;
    return data;
}