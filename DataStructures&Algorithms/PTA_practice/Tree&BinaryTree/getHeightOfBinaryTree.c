/*
 * [函数题] 求二叉树的高度
 * 本题要求给定二叉树的高度
 */

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
int GetHeight( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}

int GetHeight( BinTree BT )
{
    int maxHeight, leftHeight, rightHeight;
    if ( BT ) {
        leftHeight = GetHeight(BT->Left);
        rightHeight = GetHeight(BT->Right);
        maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;
        return ( maxHeight+1 );
    }
    return 0;
}