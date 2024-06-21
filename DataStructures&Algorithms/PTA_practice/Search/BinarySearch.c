/*
 * [函数题] 二分查找
 * 本题要求实现二分查找算法。
 * 输入样例1：
 *  5
 *  12 31 55 89 101
 *  31
 * 输出样例1:
 *  2
 * 输入样例2:
 *  3
 *  26 78 233
 *  31
 * 输出样例2:
 *  0
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};
/*
 * L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。函数BinarySearch要查找X在Data中的位置，
 * 即数组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败标记NotFound。
 */

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;
    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

Position BinarySearch( List L, ElementType X ){
    int left, right, mid;
    left = 1;
    right = L->Last;
    while (left <= right) {
        mid = (left + right) / 2;
        if (X < L->Data[mid]) right = mid - 1;
        else if (X > L->Data[mid]) left = mid + 1;
        else return mid;
    }
    return NotFound;
}

