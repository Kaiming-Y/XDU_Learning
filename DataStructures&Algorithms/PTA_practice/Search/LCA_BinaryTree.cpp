/*
 * [编程题] 二叉搜索树的最近公共祖先
 *  给定一棵二叉搜索树的先序遍历序列，要求你找出任意两结点的最近公共祖先结点（简称 LCA）。
 * 输入格式：
 *  输入的第一行给出两个正整数：待查询的结点对数 M（≤ 1 000）和二叉搜索树中结点个数 N（≤ 10 000）。随后一行给出 N 个不同的整数，为二叉搜索树的先序遍历序列。
 *  最后 M 行，每行给出一对整数键值 Key 和 Value。所有键值都在整型int范围内。
 * 输出格式：
 *  对每一对给定的 Key 和 Value，如果找到 A 是它们的最近公共祖先结点的键值，则在一行中输出 LCA of Key and Value is A.。但如果 Key 和 Value 中的一个结点是另一个结点的祖先，
 *  则在一行中输出 X is an ancestor of Y.，其中 X 是那个祖先结点的键值，Y 是另一个键值。如果 二叉搜索树中找不到以 Key 或 Value 为键值的结点，则输出 ERROR: Key is not found.
 *  或者 ERROR: Value is not found.，或者 ERROR: Key and Value are not found.。
 * 输入样例:
 *  6 8
 *  6 3 1 2 5 4 8 7
 *  2 5
 *  8 7
 *  1 9
 *  12 -3
 *  0 8
 *  99 99
 * 输出样例:
 *  LCA of 2 and 5 is 3.
 *  8 is an ancestor of 7.
 *  ERROR: 9 is not found.
 *  ERROR: 12 and -3 are not found.
 *  ERROR: 0 is not found.
 *  ERROR: 99 and 99 are not found.
 */

#include <iostream>
#define TreeNode_MAXSIZE 10000
#define CoupleNode_MAXSIZE 1000
#define ERROR -1
using namespace std;

typedef int ElementType;
typedef struct TreeNode* BinTree;
struct TreeNode{
    ElementType data;
    BinTree left, right;
};

int preOrder[TreeNode_MAXSIZE];

BinTree BuildTree(int root, int end);
BinTree Find_LCA(int key, int value, BinTree BT);
bool Find(int data, int tree[], int amount);

int main(){
    int n, m;
    cin >> m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> preOrder[i];
    }
    BinTree BT;
    BT = BuildTree(0, n-1);
    for (int i = 0; i < m; i++) {
        int Key, Value;
        cin >> Key;
        cin >> Value;
        bool foundKey, foundValue;
        foundKey = Find(Key, preOrder, n);
        foundValue = Find(Value, preOrder, n);
        if ( !foundKey && !foundValue ) {
            cout << "ERROR: " << Key << " and " << Value << " are not found." << endl;
        }
        else if ( !foundKey ) {
            cout << "ERROR: " << Key << " is not found." << endl;
        }
        else if ( !foundValue ) {
            cout << "ERROR: " << Value << " is not found." << endl;
        }
        else {
            BinTree tempTree;
            tempTree = Find_LCA(Key, Value, BT);
            if (tempTree->data == Key) {
                cout << Key << " is an ancestor of " << Value  << "." << endl;
            }
            else if (tempTree->data == Value) {
                cout << Value << " is an ancestor of " << Key  << "." << endl;
            }
            else cout << "LCA of " << Key << " and " << Value << " is " << tempTree->data << "." << endl;
        }
    }
    return 0;
}

BinTree BuildTree(int root, int end){
    if (root > end) return NULL;
    int i;
    BinTree BT;
    BT = (BinTree) malloc(sizeof(struct TreeNode));
    BT->data = preOrder[root];
    for (i = root+1; i <= end; i++) {
        if (preOrder[i] > preOrder[root]) break;
    }
    BT->left = BuildTree(root+1, i-1);
    BT->right = BuildTree(i, end);
    return BT;
}

BinTree Find_LCA(int key, int value, BinTree BT){
    BinTree T = BT;
    if (!T) return NULL;
    if (key <= T->data && value >= T->data || value <= T->data && key >= T->data) return T;
    else if (key <= T->data && value <= T->data) return Find_LCA(key, value, T->left);
    else if (key >= T->data && value >= T->data) return Find_LCA(key, value, T->right);
    else return NULL;
}

bool Find(int data, int tree[], int amount){
    for (int i = 0; i < amount; i++) {
        if (tree[i] == data) return true;
    }
    return false;
}