#include<stdio.h>
//最大子列和问题——最优算法：“在线处理” ( 时间复杂度为线性的 —— T(N) = O(N) )
int MaxSubseqSum4(int A[], int N){
    int ThisSum, MaxSum;
    int i;
    ThisSum = MaxSum = 0;
    for( i = 0; i < N; i++){
        ThisSum += A[i];
        if( ThisSum >MaxSum){
            MaxSum = ThisSum;
        }
        else if( ThisSum < 0){
            ThisSum = 0;
        }
    }
    return MaxSum;
}