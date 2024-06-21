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

//该算法空间复杂度较高

#include <stdio.h>

typedef struct NODE Node;
struct NODE{
    int address;
    int data;
    int next;
};
Node nodes[100001]; //原始数据
Node list[100001]; //顺序链表

int CreateNodes(int N, int FirstAddress);
void Rearrange(int N);
void Print(int N);

int main(){
    int N, firstAddress;
    scanf("%d %d", &firstAddress ,&N);
    N = CreateNodes(N, firstAddress);
    Rearrange(N);
    Print(N);
    return 0;
}

int CreateNodes(int N, int FirstAddress){
    int i, cnt, add, data, next;
    for(i = 0; i < N; i++){
        scanf("%d %d %d", &add, &data, &next);
        nodes[add].address = add;
        nodes[add].data = data;
        nodes[add].next = next;
    }
    //顺序存储链表, 避免出现个别输入节点不属于链表的情况
    add = FirstAddress;
    for(cnt = 0; add != -1; cnt++){
        list[cnt].address = nodes[add].address;
        list[cnt].data = nodes[add].data;
        list[cnt].next = nodes[add].next;
        add = nodes[add].next;
    }
//    for(i = 0; i < N; i++){
//        if(i!=N-1) printf("%05d %d %05d\n", list[i].address, list[i].data, list[i].next);
//        else printf("%05d %d -1\n\n", list[i].address, list[i].data);
//    }
    return cnt;
}

void Rearrange(int N){
    int p, q;
    p = 0;
    q = N-1;
    while(1){
        if (q != p) {
            list[q].next = list[p].address;
            q--;
        }
        if (p < N/2 && p != q) {
            list[p].next = list[q].address;
            p++;
        } else if (p == q) {
            list[p].next = -1;
            break;
        } else break;
    }
}

void Print(int N){
    int p, q;
    p = 0;
    q = N-1;
    while(1){
        if(N%2 == 1){
            if(p != q){
                printf("%05d %d %05d\n", list[q].address, list[q].data, list[q].next);
                q--;
                printf("%05d %d %05d\n", list[p].address, list[p].data, list[p].next);
                p++;
            }
            else{
                printf("%05d %d -1", list[q].address, list[q].data, list[q].next);
                break;
            }
        } else {
            if(p+1 != q){
                printf("%05d %d %05d\n", list[q].address, list[q].data, list[q].next);
                q--;
                printf("%05d %d %05d\n", list[p].address, list[p].data, list[p].next);
                p++;
            }
            else{
                printf("%05d %d %05d\n", list[q].address, list[q].data, list[q].next);
                printf("%05d %d -1", list[p].address, list[p].data);
                break;
            }
        }
    }
}