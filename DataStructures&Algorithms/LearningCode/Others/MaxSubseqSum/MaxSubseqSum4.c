#include<stdio.h>
//������к����⡪�������㷨�������ߴ��� ( ʱ�临�Ӷ�Ϊ���Ե� ���� T(N) = O(N) )
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