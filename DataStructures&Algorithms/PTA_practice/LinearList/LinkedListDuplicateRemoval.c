/*
 * [编程题] 链表去重
 * 给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。
 * 例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。
 * ##输入格式
 *  输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤10^5，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。
 *  随后 N 行，每行按以下格式描述一个结点：
 *      地址 键值 下一个结点
 *  其中地址是该结点的地址，键值是绝对值不超过10^4的整数，下一个结点是下个结点的地址。
 *  ##输出格式
 *   首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。
 *  ##输入样例
 *   00100 5
 *   99999 -7 87654
 *   23854 -15 00000
 *   87654 15 -1
 *   00000 -15 99999
 *   00100 21 23854
 *  ##输出样例
 *   00100 21 23854
 *   23854 -15 99999
 *   99999 -7 -1
 *   00000 -15 87654
 *   87654 15 -1
 */

#include <stdio.h>
#include <math.h>

typedef struct NODE Node;
struct NODE{
    int data;
    int next;
};
Node nodes[100001]; //原始数据

int afterRemoval[100001], delElement[100001]; //去重后的两组地址
int p1 = 0 , p2 = 0;

void CreateNodes(int N);
void DuplicateRemoval(int FirstAddress);
void Print();

int main(){
    int N, firstAddress;
    scanf("%d %d", &firstAddress ,&N);
    CreateNodes(N);
    DuplicateRemoval(firstAddress);
    Print();
    return 0;
}

void CreateNodes(int N){
    int i, add, data, next;
    for(i = 0; i < N; i++){
        scanf("%d %d %d", &add, &data, &next);
        nodes[add].data = data;
        nodes[add].next = next;
    }
}

void DuplicateRemoval(int FirstAddress) {
    int add, temp;
    int isVisited[10001] = {0};
    add = FirstAddress;
    while(add != -1){
        temp = nodes[add].data;
        if(!isVisited[abs(temp)]){ //若没出现过
            isVisited[abs(temp)] = 1;
            afterRemoval[p1++] = add;
            afterRemoval[p1] = -1;
        }
        else{ //若出现过
            delElement[p2++] = add;
            delElement[p2] = -1;
        }
        add = nodes[add].next;
    }
}

void Print(){
    int i;
    for(i = 0; i < p1; i++){
        if(afterRemoval[i+1] != -1) printf("%05d %d %05d\n", afterRemoval[i], nodes[afterRemoval[i]].data, afterRemoval[i+1]);
        else printf("%05d %d -1\n", afterRemoval[i], nodes[afterRemoval[i]].data);
    }
    for(i = 0; i < p2; i++){
        if(delElement[i+1] != -1) printf("%05d %d %05d\n", delElement[i], nodes[delElement[i]].data, delElement[i+1]);
        else printf("%05d %d -1", delElement[i], nodes[delElement[i]].data);
    }
}