/*
 * [编程题] 还原二叉树
 * 给定一棵二叉树的先序遍历序列和中序遍历序列，要求计算该二叉树的高度。
 * [输入格式]
 *  输入首先给出正整数N（≤50），为树中结点总数。下面两行先后给出先序和中序遍历序列，均是长度为N的不包含重复英文字母（区别大小写）的字符串。
 * [输出格式]
 *  输出为一个整数，即该二叉树的高度。
 * [输入样例]
 *  9
 *  ABDFGHIEC
 *  FDHGIBEAC
 * [输出样例]
 *  5
 */

#include <iostream>
using namespace std;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

int n;
string preOrder, inOrder;

int GetHeight( BinTree BT );
BinTree BuildBinTree( int root, int start, int end );

int main() {
    cin >> n;
    cin >> preOrder;
    cin >> inOrder;
    cout << GetHeight(BuildBinTree(0,0,n-1));
    return 0;
}

/*
 * 先序告诉我们根节点, 中序可以依据根节点得到左右子树包含的元素, 那么再回到先序中, 寻找左右子树的根节点, 然后进入中序寻找下一层的左右子树, 如此深入, 直到还原二叉树.
 * 由于先序遍历即依次访问一个二叉树的每个结点, 所以构造二叉树的元素顺序采用先序遍历的顺序.
 */

int GetHeight( BinTree BT )
{
    int maxHeight, leftHeight, rightHeight;
    if ( BT ) {
        leftHeight = GetHeight(BT->Left); //计算左子树的深度
        rightHeight = GetHeight(BT->Right); //计算右子树的深度
        maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight; //比较左右子树的深度, 选取更大者
        return ( maxHeight+1 ); //由于算上根节点的一层深度, 对于子树深度还要+1, 才是这棵树的深度
    }
    return 0;
}

BinTree BuildBinTree( int root, int start, int end ) //root代表待还原二叉树的根节点, start为中序中子树的起始元素的位置, end为中序中子树的结尾元素的位置.
{
    if ( start > end ) return NULL; //若该树在中序中的起始位置位于结束位置之后, 则说明该树已经遍历完成, 即还原完毕
    BinTree BT;
    BT = (BinTree) malloc(sizeof (struct TNode));
    int i;
    for( i = start; i <= end; i++){
        if ( inOrder[i] == preOrder[root] ) break; //遍历树在中序中的部分, 依据于前序得到的根节点寻找该树的根节点位置, 用于找到出该树中的左右子树
    }
    //因为是根据先序遍历的次序还原二叉树的, 所以直接先构建根节点, 再构建其子树
    //找到该根结点, 并为其赋值, 其左右子树经上述循环已经得到, 所以直接分别传入其左右子树的起始于结束位置即可:
    BT->Data = preOrder[root];
    BT->Left = BuildBinTree(root+1, start, i-1);
    BT->Right = BuildBinTree(root+i-start+1, i+1, end);
    return BT;
}