#include<stdio.h>
//Ê±¼ä¸´ÔÓ¶È ¡ª¡ª T(N) = O(N^3)
int MaxSubseqSum1(int A[], int N){
    int ThisSum, MaxSum = 0 ;
    int i, j , k;
    for( i = 0; i < N; i++){
        for( j = i; j < N; j++){
            ThisSum = 0;
            for ( k =i; k<= j; k++){
                ThisSum += A[k];
            }
            if( ThisSum > MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}