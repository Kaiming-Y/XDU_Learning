/*
 * [编程题]
 * [题目名称] 古风排版
 * [题目描述]
 *  中国的古人写文字，是从右向左竖向排版的。本题就请你编写程序，把一段文字按古风排版。
 * [输入格式]
 *  输入在第一行给出一个正整数N（<100），是每一列的字符数。第二行给出一个长度不超过1000的非空字符串，以回车结束。
 * [输出格式]
 *  按古风格式排版给定的字符串，每列N个字符（除了最后一列可能不足N个）。
 * [输入样例]
 *  4
 *  This is a test case
 * [输出样例]
 *  asa T
 *  st ih
 *  e tsi
 *   ce s
 */

#include <iostream>
#include <string>
using namespace std;

int main(){
    int charNumber;
    int length, rowAmount, colAmount, firstColNumber;
    string sentence;
    cin >> charNumber;
    getchar();
    getline(cin,sentence);
    length = (int)sentence.size();
    rowAmount = charNumber;
    firstColNumber = length % charNumber;
    if (firstColNumber != 0) {
        colAmount = length / charNumber + 1;
    } else {
        colAmount = length / charNumber;
    }
    int i, j;
    for (i = 0; i < rowAmount; i++) {
        for ( j = colAmount - 1; j >= 0; j--) {
            if (firstColNumber != 0){
                if (j == colAmount -1 && i >= firstColNumber) cout << ' ';
                else {
                    cout << sentence[j*charNumber+i];
                }
            } else {
                cout << sentence[j*charNumber+i];
            }
        }
        if(i < rowAmount -1){
            cout << '\n';
        }
    }
    return 0;
}