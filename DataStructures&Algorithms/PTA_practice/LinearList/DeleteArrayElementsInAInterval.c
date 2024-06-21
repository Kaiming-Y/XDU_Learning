/*
 * [函数题] 数组元素的区间删除
 * 给定一个顺序存储的线性表，请设计一个函数删除所有值大于min而且小于max的元素。删除后表中剩余元素保持顺序存储，并且相对位置不能改变。
 * 函数接口定义:
 *  int Delete( int A[], int L, int minA, int maxA );
 * 其中A是整型数组，存储原始线性表的元素；L是表长，即A中元素的个数；minA和maxA分别为待删除元素的值域的下、上界。函数Delete应将A中所有值大于minA而且小于maxA的元素删除，同时保证表中剩余元素保持顺序存储，并且相对位置不变，最后返回删除后的表长。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 20

typedef struct LNode *List;
struct LNode{
    int data;
    List next;
};

int Delete( int A[], int L, int minA, int maxA );

int main()
{
    int A[MAXN], L, minA, maxA, i;

    scanf("%d", &L);
    for (i=0; i<L; i++) scanf("%d", &A[i]);
    scanf("%d %d", &minA, &maxA);
    L = Delete(A, L, minA, maxA);
    printf("%d\n",L);
    for (i=0; i<L; i++) printf("%d ", A[i]);
    printf("\n");

    return 0;
}

int Delete( int A[], int L, int minA, int maxA ){
    int i;
    //链式存储线性表(构造链表)
    List list, p, t, s; //list始终指向表头
    list = (List)malloc(sizeof(struct LNode));
    list->data = A[0];
    list->next = NULL;
    p = list;
    for (i=1; i<L; i++){
        t = (List)malloc(sizeof(struct LNode));
        t->data = A[i];
        t->next = NULL;
        p->next = t;
        p = t;
    }
    //遍历链表, 删除minA与maxA之间的元素
    p = list;
    t = list;
    while(p != NULL){
        if(p->data > minA && p->data < maxA){
            if(p == list){ //若删除的节点在表头
                s = p;
                if(list != NULL){
                    list = list->next;
                    p = p->next;
                    t = t->next;
                }
                else return 0;
                free(s);
                L--; //长度减1
            }
            else{ //若删除的节点不在表头
                while(t->next != p) t = t->next; //查找该节点的上一个节点
                s = p;
                p = p->next;
                t->next = p;
                free(s);
                L--; //长度减1
            }
        }
        else{
            p = p->next;
        }
    }
    //将链表还原成数组
    memset(A, 0, sizeof(A));
    p = list;
    for(i=0; i<L && p != NULL; i++){
        A[i] = p->data;
        p = p->next;
    }
    return L;
}
