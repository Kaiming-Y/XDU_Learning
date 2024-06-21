/*
 * 题目名称: 判定是否是同一棵二叉搜索树
 * 题目描述: 给定一个插入序列就可以唯一确定一棵二叉搜索树. 然而, 一棵给定的二叉搜索树却可以由多种不同的插入序列得到. 对于输入的各种插入序列, 你需要判断它是否能生成一样的二叉搜索树.
 *         第一行输入树的节点数N, 和有L个二叉搜索树参与判定(除去原始树); 第二行输入N个数表示原始树的输入顺序; 随后L行分别输入待判定的数的输入顺序. 输入0退出.
 * ###输入样例:
 * 4 2
 * 3 1 4 2
 * 3 4 2 1
 * 3 2 4 1
 * 0
 * ###输出样例:
 * Yes
 * No
 */

/*
 * 求解思路:
 * 1.(原)搜素树表示
 * 2.建搜索树T
 * 3.判别一序列是否与搜索树T一致
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode{
    int v;
    Tree left, right;
    int flag; //标识该节点是否被查找过
};

Tree MakeTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int Judge(Tree T, int N);
int Check(Tree T, int V);
void Reset(Tree T); //释放T中各节点的flag标记
void FreeTree(Tree T); //释放T的空间

int main() {
    int N, L, i;
    Tree T;
    scanf("%d",&N);
    while(N){
        scanf("%d",&L);
        T = MakeTree(N);
        for(i=0; i<L; i++){
            if(Judge(T, N)) printf("Yes\n");
            else printf("No\n");
            Reset(T); //清除T中的标记flag
        }
        FreeTree(T);
        scanf("%d",&N);
    }
    return 0;
}

Tree MakeTree(int N){
    Tree T;
    int i, V;
    scanf("%d",&V);
    T = NewNode(V);
    for(i=1; i<N; i++){
        scanf("%d",&V);
        T = Insert(T, V);
    }
    return T;
}

Tree NewNode(int V){
    Tree T = (Tree)malloc(sizeof (struct TreeNode));
    T->v = V;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}

Tree Insert(Tree T, int V){
    if(!T) T = NewNode(V);
    else{
        if(V > T->v)
            T->right = Insert(T, V);
        else
            T->left = Insert(T, V);
    }
    return T;
}

int Judge(Tree T, int N){
    int i, V, flag = 0; //flag: 0 代表目前还一致, 1 代表已经不一致
    scanf("%d",&V);
    if(V != T->v) flag = 1;
    else T->flag = 1;
    for(i=1; i<N; i++){
        scanf("%d",&V);
        if((!flag) && (!Check(T, V))) flag = 1;
    }
    if(flag) return 0;
    else return 1;
}

int Check(Tree T, int V){
    if(T->flag){
        if(V < T->v) return Check(T->left, V);
        else if(V > T->v) return Check(T->right, V);
        else return 0;
    }
    else{
        if(V == T->v){
            T->flag = 1;
            return 1;
        }
        else return 0;
    }
}

void Reset(Tree T){
    if(T->left) Reset(T->left);
    if(T->right) Reset(T->right);
    T->flag = 0;
}

void FreeTree(Tree T){
    if(T->left) FreeTree(T->left);
    if(T->right) FreeTree(T->right);
    free(T);
}