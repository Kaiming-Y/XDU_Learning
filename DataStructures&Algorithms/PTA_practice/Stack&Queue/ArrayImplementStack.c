/*
 * [函数题]
 * 本题要求在一个数组中实现两个堆栈。
 * 函数接口定义：
 *  Stack CreateStack( int MaxSize );
 *  bool Push( Stack S, ElementType X, int Tag );
 *  ElementType Pop( Stack S, int Tag );
 * 其中Tag是堆栈编号，取1或2；MaxSize堆栈数组的规模；Stack结构定义如下：
 * typedef int Position;
 *  struct SNode {
 *  ElementType *Data;
 *  Position Top1, Top2;
 *  int MaxSize;
 *  };
 *  typedef struct SNode *Stack;
 * 注意：如果堆栈已满，Push函数必须输出“Stack Full”并且返回false；如果某堆栈是空的，则Pop函数必须输出“Stack Tag Empty”（其中Tag是该堆栈的编号），并且返回ERROR。
 * 输入样例：
 * 5
 * Push 1 1
 * Pop 2
 * Push 2 11
 * Push 1 2
 * Push 2 12
 * Pop 1
 * Push 2 13
 * Push 2 14
 * Push 1 3
 * Pop 2
 * End
 * 输出样例：
 * Stack 2 Empty
 * Stack 2 is Empty!
 * Stack Full
 * Stack 1 is Full!
 * Pop from Stack 1: 1
 * Pop from Stack 2: 13 12 11
 */

#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
struct SNode {
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );
bool Push( Stack S, ElementType X, int Tag );
ElementType Pop( Stack S, int Tag );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Tag ); /* details omitted */

int main()
{
    int N, Tag, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
            case push:
                scanf("%d %d", &Tag, &X);
                if (!Push(S, X, Tag)) printf("Stack %d is Full!\n", Tag);
                break;
            case pop:
                scanf("%d", &Tag);
                X = Pop(S, Tag);
                if ( X==ERROR ) printf("Stack %d is Empty!\n", Tag);
                break;
            case end:
                PrintStack(S, 1);
                PrintStack(S, 2);
                done = 1;
                break;
        }
    }
    return 0;
}

Stack CreateStack( int MaxSize ){
    Stack S =(Stack) malloc(sizeof (struct SNode));
    S->MaxSize = MaxSize;
    S->Data = (ElementType *) malloc(MaxSize*sizeof (ElementType));
    //使两个栈分别从数组的两头开始
    S->Top1 = -1;
    S->Top2 = MaxSize;
    return S;
}

bool Push( Stack S, ElementType X, int Tag ){
    if (S->Top2 - S->Top1 == 1) {
        printf("Stack Full\n");
        return false;
    }
    if (Tag == 1) {
        S->Data[++(S->Top1)] = X;
    } else {
        S->Data[--(S->Top2)] = X;
    }
    return true;
}

ElementType Pop( Stack S, int Tag ){
    if (Tag == 1) {
        if (S->Top1 == -1) {
            printf("Stack %d Empty\n", Tag);
            return ERROR;
        } else {
            return S->Data[(S->Top1)--];
        }
    } else {
        if (S->Top2 == S->MaxSize) {
            printf("Stack %d Empty\n", Tag);
            return ERROR;
        } else {
            return S->Data[(S->Top2)++];
        }
    }
}
