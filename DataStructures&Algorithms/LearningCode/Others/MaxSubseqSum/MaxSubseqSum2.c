#include<stdio.h>
//Ê±¼ä¸´ÔÓ¶È ¡ª¡ª T(N) = O(N^2)
int MaxSubseqSum2(int A[], int N){
    int ThisSum, MaxSum = 0 ;
    int i, j;
    for( i = 0; i < N; i++){
        ThisSum = 0;
        for( j = i; j < N; j++){
            ThisSum += A[j];
            if( ThisSum > MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}