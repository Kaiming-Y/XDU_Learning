/*
 * [函数题] 删除单链表偶数节点
 * 本题要求实现两个函数，分别将读入的数据存储为单链表、将链表中偶数值的结点删除。链表结点定义如下：
 *   struct ListNode {
 *      int data;
 *      struct ListNode *next;
 *   };
 * 函数接口定义：
 *   struct ListNode *createlist();
 *   struct ListNode *deleteeven( struct ListNode *head );
 * 函数createlist从标准输入读入一系列正整数，按照读入顺序建立单链表。当读到−1时表示输入结束，函数应返回指向单链表头结点的指针。
 * 函数deleteeven将单链表head中偶数值的结点删除，返回结果链表的头指针。
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist();
struct ListNode *deleteeven( struct ListNode *head );
void printlist( struct ListNode *head )
{
    struct ListNode *p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    struct ListNode *head;

    head = createlist();
    head = deleteeven(head);
    printlist(head);

    return 0;
}

struct ListNode *createlist(){
    int t;
    struct ListNode *p, *head;
    head = (struct ListNode *)malloc(sizeof (struct ListNode));
    scanf("%d", &t);
    if(t != -1){
        head->data = t;
        head->next = NULL;
        p = head;
    }
    else{
        return NULL;
    }
    scanf("%d", &t);
    while(t != -1){
        struct ListNode *s;
        s = (struct ListNode *)malloc(sizeof (struct ListNode));
        s->data = t;
        s->next = NULL;
        p->next = s;
        p = p->next;
        scanf("%d", &t);
    }
    return head;
}

struct ListNode *deleteeven( struct ListNode *head ){
    struct ListNode *p, *s, *t;
    p = head;
    t = head;
    while(p != NULL){
        if(p->data % 2 == 0){ //若值为偶数
            if(p == head){
                s = p;
                if( head!=NULL ){
                    head = head->next;
                    p = head;
                    t = head;
                }
                else return NULL;
                free(s);
            }
            else{
                while(t->next != p) t = t->next;
                s = p;
                p = p->next;
                t->next = p;
                free(s);
            }
        }
        else{
            p = p->next;
        }
    }
    return head;
}