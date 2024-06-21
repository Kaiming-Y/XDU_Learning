/*
 * [函数题] 快速排序
    给一个无序表，使用快速排序算法对它进行排序。
# 函数接口定义：
    int Partition(SqList &L,int low,int high);
    void QuickSort(SqList &L, int low, int high);
        其中L是待排序表，low和high是排序的区间。
# 输入样例：
    在这里填写一组输入
    5
    3 1 9 5 7
# 输出样例：
    1 3 5 7 9
# 输入样例：
    在这里填写一组输入
    5
    0 -1 8 -1 2
# 输出样例：
    -1 -1 0 2 8
 */

#include <iostream>
using namespace std;

#define MAXSIZE 50
typedef int KeyType;

typedef struct
{
    KeyType  key;
} ElemType;

typedef struct
{
    ElemType r[MAXSIZE+1];
    int length;
} SqList;

void Create(SqList &L)
{
    int i;
    cin >> L.length;
    for(i=1; i<=L.length; i++) cin>>L.r[i].key;
}

void Output(SqList L)
{
    int i;
    for(i=1; i<=L.length; i++) cout << L.r[i].key << " ";
    cout << endl;;
}

int Partition(SqList &L,int low,int high);
void QuickSort(SqList &L, int low, int high);

int main ()
{
    SqList L;
    int low,high;
    Create(L);
    low=1;
    high=L.length;
    QuickSort(L,low,high);
    Output(L);
    return 0;
}

int Partition(SqList &L,int low,int high){
    int base = L.r[low].key;
    while (low < high){
        while (low < high && L.r[high].key >= base) high--;
        L.r[low].key = L.r[high].key;
        while (low < high && L.r[low].key <= base) low++;
        L.r[high].key = L.r[low].key;
    }
    L.r[low].key = base;
    return low;
}

void QuickSort(SqList &L, int low, int high){
    if (low < high){
        int base = Partition(L, low, high);
        QuickSort(L, low, base-1);
        QuickSort(L, base+1, high);
    }
}
