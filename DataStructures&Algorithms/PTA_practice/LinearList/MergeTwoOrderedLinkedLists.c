/*
 * [编程题] 两个有序链表序列的合并
 * 已知两个非降序链表序列S1与S2，设计函数构造出S1与S2合并后的新的非降序链表S3。
 * 输入格式:
 *  输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。
 * 输出格式:
 *  在一行中输出合并后新的非降序链表，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
 * 输入样例:
 *  1 3 5 -1
 *  2 4 6 8 10 -1
 * 输出样例:
 *  1 2 3 4 5 6 8 10
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node *List;
struct Node{
    int data;
    List next;
};

List Read();
void Print(List L);
List Merge(List L1, List L2);

int main(){
    List l1, l2, L;
    l1 = Read();
    l2 = Read();
    L = Merge(l1, l2);
    Print(L);
}

List Read(){
    List head, p, s;
    head = (List) malloc(sizeof (struct Node));
    int t;
    scanf("%d", &t);
    if(t != -1){
        head->data = t;
        head->next = NULL;
    }
    else return NULL;
    p = head;
    scanf("%d", &t);
    while(t != -1){
        s = (List) malloc(sizeof (struct Node));
        s->data = t;
        s->next = NULL;
        p->next = s;
        p = p->next;
        scanf("%d", &t);
    }
    return head;
}

void Print(List L){
    if(!L){
        printf("NULL");
        return ;
    }
    List p = L;
    while (p) {
        printf("%d", p->data);
        if(p->next != NULL) printf(" ");
        p = p->next;
    }
}

List Merge(List L1, List L2){
    if( L1 == NULL && L2 == NULL) return NULL;
    List p1 = L1;
    List p2 = L2;
    List L, p;
    L = (List) malloc(sizeof (struct Node));
    p = L;
    while(p1 && p2){
        if(p1->data < p2->data){
            p->next = p1;
            p1 = p1->next;
        }
        else{
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }
    if (p1) p->next = p1;
    if (p2) p->next = p2;
    return L->next;
}