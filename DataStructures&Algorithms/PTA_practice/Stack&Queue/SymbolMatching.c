/*
 * [编程题]
 * 请编写程序检查C语言源程序中下列符号是否配对：/ *与* /、(与)、[与]、{与}。
 * 输入格式:
 * 输入为一个C语言源程序。当读到某一行中只有一个句点.和一个回车的时候，标志着输入结束。程序中需要检查配对的符号不超过100个。
 * 输出格式:
 * 首先，如果所有符号配对正确，则在第一行中输出YES，否则输出NO。然后在第二行中指出第一个不配对的符号：如果缺少左符号，则输出?-右符号；如果缺少右符号，则输出左符号-?。
 * 输入样例1：
 * void test()
 * {
 *  int i, A[10];
 *  for (i=0; i<10; i++) { / * /
 *  A[i] = i;
 * }
 * .
 * 输出样例1：
 * NO
 * / *-?
 * 输入样例2：
 * void test()
 * {
 *   int i, A[10];
 *   for (i=0; i<10; i++) / * * /
 *   A[i] = i;
 *   }]
 * .
 * 输出样例2：
 * NO
 * ?-]
 * 输入样例3：
 * void test()
 * {
 *  int i
 *  double A[10];
 *  for (i=0; i<10; i++) / * * /
 *      A[i] = 0.1*i;
 *      }
 * 输出样例3：
 * YES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define MAXSIZE 100

typedef enum { false, true } bool;

typedef struct SNode *PtrToSNode;
struct SNode {
    union {
        char Symbol;
        int Count;
    };
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreatStack();
bool Push(char item, Stack S);
char Pop(Stack S);
char Top(Stack S);
bool isFull(Stack S);
bool isEmpty(Stack S);

int main(){
    Stack S;
    S = CreatStack();
    char symbol;
    char str[1000];
    while(true){
        gets(str);
        if(str[0]=='.') break;
        int length = strlen(str);
        int i;
        for(i=0; i<length; i++){
            char c;
            switch (str[i]) {
                case '(':
                    Push('(', S);
                    break;
                case '[':
                    Push('[', S);
                    break;
                case '{':
                    Push('{', S);
                    break;
                case ')':
                    if (!isEmpty(S)) {
                        c = Pop(S);
                    } else {
                        c = ERROR;
                    }
                    if(c == '(') break; //匹配成功
                    else {
                        printf("NO\n");
                        if (isEmpty(S)) {
                            printf("?-)");
                        } else if (c == '<') {
                            printf("/*-?");
                        } else {
                            printf("%c-?", c);
                        } //匹配不成功
                        return 0;
                    }
                case ']':
                    if (!isEmpty(S)) {
                        c = Pop(S);
                    } else {
                        c = ERROR;
                    }
                    if(c == '[') break; //匹配成功
                    else {
                        printf("NO\n");
                        if (isEmpty(S)) {
                            printf("?-]");
                        } else if (c == '<') {
                            printf("/*-?");
                        } else {
                            printf("%c-?", c);
                        } //匹配不成功
                        return 0;
                    }
                case '}':
                    if (!isEmpty(S)) {
                        c = Pop(S);
                    } else {
                        c = ERROR;
                    }
                    if(c == '{') break; //匹配成功
                    else {
                        printf("NO\n");
                        if (isEmpty(S)) {
                            printf("?-}");
                        } else if (c == '<') {
                            printf("/*-?");
                        } else {
                            printf("%c-?", c);
                        } //匹配不成功
                        return 0;
                    }
                case '/':
                    if (str[i+1] == '*') {
                        Push('<', S); //用<表示/*
                        i++;
                        break;
                    } else {
                        break;
                    }
                case '*':
                    if (str[i+1] == '/') {
                        c = Pop(S);
                        if (c == '<') {
                            i++;
                            break; //匹配成功
                        }
                        else {
                            printf("NO\n");
                            if (isEmpty(S)) {
                                printf("?-*/");
                            } else {
                                printf("%c-?", c); //匹配不成功
                            }
                            return 0;
                        }
                    } else {
                        break;
                    }
                default:
                    break;
            }
        }

    }
    if(isEmpty(S)){
        printf("YES\n");
    } else {
        printf("NO\n");
        if (Top == '<') {
            printf("/*-?");
        } else {
            printf("%c-?", Top(S));
        }
    }
    return 0;
}

Stack CreatStack(){
    Stack S;
    S = (Stack) malloc(sizeof (struct SNode));
    S->Count = 0;
    S->Next = NULL;
    return S;
}

bool Push(char item, Stack S){
//    if ( isFull(S) ) {
//        printf("Stack is Full\n");
//        return false;
//    }
    Stack tmpCell;
    tmpCell = (Stack) malloc(sizeof (struct SNode));
    tmpCell->Symbol = item;
    tmpCell->Next = S->Next;
    S->Next = tmpCell;
    S->Count++;
    return true;
}

char Pop(Stack S){
    if ( isEmpty(S) ) {
//        printf("Stack is Empty\n");
        return ERROR;
    }
    Stack tmpCell;
    char tmpSymbol;
    tmpCell = S->Next;
    tmpSymbol = tmpCell->Symbol;
    S->Next = tmpCell->Next;
    S->Count--;
    free(tmpCell);
    return tmpSymbol;
}

char Top(Stack S){
    if(isEmpty(S)) return ERROR;
    return S->Next->Symbol;
}

bool isFull(Stack S){
    return (S->Count == MAXSIZE);
}

bool isEmpty(Stack S){
    return ( S->Next == NULL );
}
