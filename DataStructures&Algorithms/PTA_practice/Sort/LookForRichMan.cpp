/*
 * [编程题] 寻找大富翁
 *  胡润研究院的调查显示，截至2017年底，中国个人资产超过1亿元的高净值人群达15万人。假设给出N个人的个人资产值，请快速找出资产排前M位的大富翁。
 * #输入格式:
 *  输入首先给出两个正整数N（≤10^6）和M（≤10），其中N为总人数，M为需要找出的大富翁数；接下来一行给出N个人的个人资产值，以百万元为单位，为不超过长整型范围的整数。数字间以空格分隔。
 * #输出格式:
 *  在一行内按非递增顺序输出资产排前M位的大富翁的个人资产值。数字间以空格分隔，但结尾不得有多余空格。
 * #输入样例:
 *  8 3
 *  8 12 7 3 20 9 5 18
 * #输出样例:
 *  20 18 12
 */

#include <iostream>
using namespace std;

int cmp(const void *a, const void *b);

int main(){
    int N, M;
    cin >> N >> M;
    int array[N];
    for(int i = 0; i < N; i++) {
        cin >> array[i];
    }
    qsort(array, N, sizeof (array[0]), cmp);
    if (M < N) {
        for (int i = 0; i < M; i++){
            cout << array[i];
            if ( i != M-1 ) cout << " ";
        }
    } else {
        for (int i = 0; i < N; i++){
            cout << array[i];
            if ( i != N-1 ) cout << " ";
        }
    }
    return 0;
}

int cmp(const void *a, const void *b){
    return (*(int *)b - *(int *)a);
}