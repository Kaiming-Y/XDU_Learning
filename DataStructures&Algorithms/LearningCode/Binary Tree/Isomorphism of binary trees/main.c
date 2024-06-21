/*
 * 题目名称: 二叉树的同构
 * 题目描述: 给定两棵二叉树T1和T2. 如果T1可以通过若干次左右孩子互换变成T2, 则我们称两棵树是同构的. 现给定两棵树, 判断是否同构.
 * 输入格式: 输入给出2棵二叉树的信息: 先在一行中给出该树的节点数, 随后N行, 第i行对应编号为i的节点中存储的字母和左孩子节点的编号以及右孩子节点的编号. 如果孩子节点为空, 则在相应位置上给出"-"
 * ##输入样例:
 * 8
 * A 1 2
 * B 3 4
 * C 5 -
 * D - -
 * E 6 -
 * G 7 -
 * F - -
 * H - -
 */

//本题采用数组结构表示二叉树: 静态链表

#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{
    ElementType element;
    Tree left;
    Tree right;
}T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1,Tree R2);

int main() {
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if(Isomorphic(R1,R2)) printf("Yes\n");
    else printf("No\n");
    return 0;
}

Tree BuildTree(struct TreeNode T[]){
    int N;
    int i;
    char cl, cr;
    Tree Root;
    scanf("%d",&N);
    int check[N+1]; //标记是否是某个节点的子节点
    if(N){
        for(i=0; i<N; i++) check[i] = 0;
        for(i=0; i<N; i++){
            scanf("%c %c %c\n", &T[i].element, &cl, &cr);
            if(cl != '-'){
                T[i].left = cl - '0';
                check[T[i].left] = 1;
            }
            else T[i].left = Null;
            if(cr != '-'){
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else T[i].right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i]) break; //寻找根root
        Root = i;
    }
    return Root;
}

int Isomorphic(Tree R1,Tree R2){
    if((R1 == Null) && (R2 == Null)) //两个根节点都为空
        return 1;
    if(((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null))) //两个节点中只有一个为空
        return 0;
    if(T1[R1].element != T2[R2].element) //两个节点元素不一样
        return 0;
    if((T1[R1].left == Null) && (T2[R2].left == Null)) //两个节点的左孩子节点都为空
        return Isomorphic(T1[R1].right, T2[R2].right);
    if(((T1[R1].left != Null) && (T2[R2].left != Null)) && (T1[T1[R1].left].element == T2[T2[R2].left].element)) //不需要替换左右孩子节点
        return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
    else //替换左右孩子节点
        return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T2[R2].left, T1[R1].right));
}