/*
 * ###题目: 一元多项式的加法和乘法
 * ###题目描述:
 *  已知两个多项式:
 *  (1) 3x^4 - 5x^2 + 6x - 2
 *  (2) 5x^20 - 7x^4 + 3x
 *  多项式和:
 *   5x^20 - 7x^4 + 3x
 *  多项式积:
 *   15x^24 - 25x^22 + 30x^21 - 10x^20 - 21x^8 + 35x^6 - 33x^5 + 14x^4 - 15x^3 + 18x^2 - 6x
 *  --要求输入时:两个多项式分两行输入,每行先输入项数N,在依次输入N个数的系数和指数
 *  --要求先后输出积(第一行)与和(第二行)的结果
 *  ###输入样例:
 *   4 3 4 -5 2 6 1 -2 0
 *   3 5 20 -7 4 3 1
 *  ###输出样例:
 *   15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
 *   5 20 -4 4 -5 2 9 1 -2 0
 */

//本次采用链表实现该题算法

#include <stdio.h>
#include <stdlib.h>

//数据结构设计
typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef; //系数
    int expon; //指数
    Polynomial link;
};

Polynomial ReadPoly();
Polynomial Mult(Polynomial p1, Polynomial p2);
Polynomial Add(Polynomial p1, Polynomial p2);
void PrintPoly(Polynomial p);
void Attach(int c, int e, Polynomial *pRear);

int main() {
    Polynomial P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    printf("\n");
    PS = Add(P1,P2);
    PrintPoly(PS);
    return 0;
}

Polynomial ReadPoly(){
    int N, c, e;
    Polynomial Rear, P, t;
    scanf("%d",&N);
    P = (Polynomial) malloc(sizeof (struct PolyNode)); //链表头空节点
    P->link = NULL;
    Rear = P; //开始时尾节点指向头节点
    while(N--){
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear); //将当前项插入多项式尾部
    }
    //删除临时生成的空节点:
    t = P;
    P = P->link;
    free(t);
    return P;
}

Polynomial Mult(Polynomial p1, Polynomial p2) {
    Polynomial P, Rear, t1, t2, t;
    int c, e;
    if(!p1 || !p2) return NULL;
    t1 = p1;
    t2 = p2;
    P = (Polynomial) malloc(sizeof (struct PolyNode));
    P->link = NULL;
    Rear = P;
    //先将p1的第一项与p2每项相乘:
    for (; t2; t2 = t2->link) Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
    t1 = t1->link;
    //从p1第二项开始依次与p2每项相乘:
    for(; t1; t1 = t1->link){
        t2 = p2;
        Rear = P;
        for(; t2; t2 = t2->link){
            c = t1->coef * t2->coef;
            e = t1->expon + t2->expon;
            //按照指数递减的词次序, 不断寻找合适的插入位置
            while(Rear->link && Rear->link->expon > e){
                Rear = Rear->link;
            }
            if(Rear->link && Rear->link->expon == e){
                if(Rear->link->coef + c){
                    Rear->link->coef += c;
                }
                else{
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else{
                t = (Polynomial) malloc(sizeof (struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
        }
    }
    t = P;
    P = P->link;
    free(t);
    return P;
}

Polynomial Add(Polynomial p1, Polynomial p2) {
    Polynomial P, Rear, temp; //P记录结果多项式链表头节点, Rear记录多项式链表尾节点
    int sum;
    P = (Polynomial) malloc(sizeof (struct PolyNode));
    P->link = NULL;
    Rear =  P;
    //依次比较两的多项式各项指数是否相等, 若相等则系数相加, 若不等则将指数大者加到结果多项式链表尾部:
    while (p1 && p2){
        if(p1->expon == p2->expon){
            sum = p1->coef + p2->coef;
            if(sum) Attach(sum, p1->expon, &Rear);
            p1 = p1->link;
            p2 = p2->link;
        }
        else if(p1->expon > p2->expon){
            Attach(p1->coef, p1->expon, &Rear);
            p1 = p1->link;
        }
        else {
            Attach(p2->coef, p2->expon, &Rear);
            p2 = p2->link;
        }
    }
    //将未处理完的另一个多项式的项的所有节点依次复制到结果多项式中
    for (; p1; p1 = p1->link) Attach(p1->coef, p1->expon, &Rear);
    for (; p2; p2 = p2->link) Attach(p2->coef, p2->expon, &Rear);
    Rear->link = NULL;
    temp = P;
    P = P->link; //使P指向多项式第一个非零项中
    free(temp); //释放临时空表头节点
    return P;
}

void PrintPoly(Polynomial p) {
    int flag = 0; //辅助调整输出格式用
    if(!p) {
        printf("0 0");
        return ;
    }
    for(; p; p = p->link){
        if(!flag) flag = 1;
        else printf(" ");
        printf("%d %d", p->coef, p->expon);
    }
}

void Attach(int c, int e, Polynomial *pRear) {
    Polynomial P;
    P = (Polynomial) malloc(sizeof (struct PolyNode));
    //对新节点赋值:
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P; //将新节点连接到链表尾部
    *pRear = P; //修改pRear值
}