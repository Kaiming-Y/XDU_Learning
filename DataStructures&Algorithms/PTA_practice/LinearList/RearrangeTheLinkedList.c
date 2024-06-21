/*
 * [编程题] 重排链表
 * 给定一个单链表L1->L2->...->Ln-1->Ln，请编写程序将链表重新排列为Ln->L1->Ln-1->L2->...。例如给定L为1→2→3→4→5→6，则输出应该为6→1→5→2→4→3。
 * ##输入格式:
 *  每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址和结点总个数，即正整数N (≤10^5)。结点的地址是5位非负整数，NULL地址用−1表示。
 *  接下来有N行，每行格式为：
 *      Address Data Next
 *  其中Address是结点地址；Data是该结点保存的数据，为不超过10^5的正整数；Next是下一结点的地址。题目保证给出的链表上至少有两个结点。
 * ##输出格式:
 *  对每个测试用例，顺序输出重排后的结果链表，其上每个结点占一行，格式与输入相同。
 * ##输入样例:
 *  00100 6
 *  00000 4 99999
 *  00100 1 12309
 *  68237 6 -1
 *  33218 3 00000
 *  99999 5 68237
 *  12309 2 33218
 * ##输出样例:
 *  68237 6 00100
 *  00100 1 99999
 *  99999 5 12309
 *  12309 2 00000
 *  00000 4 33218
 *  33218 3 -1
 */

//该算法时间复杂度较高

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE Node;
struct NODE{
    int address;
    int data;
    int next;
};
Node node[100001];

typedef struct Plist *List;
struct Plist{
    int data;
    List next;
};

List CreatList(int N, int FirstAddress);
List Rearrange(List L, int N);
List reverse(List head);
void Print(List L, int N);

int main(){
    int firstAdd, N;
    scanf("%d %d", &firstAdd, &N);
    List L;
    L = CreatList(N, firstAdd);
    L = Rearrange(L, N);
    Print(L, N);
    return 0;
}

List CreatList(int N, int FirstAddress){
    int i, j;
    for(i = 0; i < N; i++){
        scanf("%d %d %d", &node[i].address, &node[i].data, &node[i].next);
    }
    //将模拟链表转化成实际链表
    List head, p;
    int add = FirstAddress;
    head = (List) malloc(sizeof (struct Plist));
    head->next = NULL;
    p = head;
    for(i = 0; i < N; i++){
        List s;
        s = (List) malloc(sizeof (struct Plist));
        for(j = 0; j < N; j++){
            if(node[j].address == add){
                s->data = node[j].data;
                add = node[j].next;
                break;
            }
        }
        s->next = NULL;
        p->next = s;
        p = p->next;
        if (node[j].next == -1 && i != N-1){
            printf("Nodes Error!");
            return NULL;
        }
    }
    return head->next;
}

List Rearrange(List L, int N){
    int i;
    List l1, l2, l, p;
    l = (List) malloc(sizeof (struct Plist));
    l->next = NULL;
    p = l;
    l1 = L;
    l2 = L;
    for (i = 0; i < N/2; i++){
        List t;
        t = l2;
        l2 = l2->next;
        if (i == N/2 - 1) t->next = NULL;
    }
    l2 = reverse(l2);
    while(l1 || l2){
        p->next = l2;
        p = p->next;
        l2 = l2->next;
        if(l1){
            p->next = l1;
            p = p->next;
            l1 = l1->next;
        }
    }
    p->next = NULL;
    return l->next;
}

List reverse(List head){
    if(head == NULL) return NULL;
    List q, p, s;
    q = head;
    p = head->next;
    while(p != NULL){
        s = p->next;
        p->next = q;
        q = p;
        p = s;
    }
    head->next = NULL;
    return q;
}

void Print(List L, int N){
    int i, j, k;
    List p = L;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(node[j].data == p->data){
                if(p->next == NULL){
                    node[j].next = -1;
                }
                else{
                    for(k = 0; k < N; k++){
                        if (node[k].data == p->next->data){
                            node[j].next = node[k].address;
                            break;
                        }
                    }
                }
                if(node[j].next != -1) printf("%05d %d %05d\n", node[j].address, node[j].data, node[j].next);
                else printf("%05d %d -1", node[j].address, node[j].data);
                break;
            }
        }
        p = p->next;
    }
}