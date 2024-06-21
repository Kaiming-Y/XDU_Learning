/*
 * [编程题]
 * [题目名称] 串的模式匹配 (KMP算法)
 * [题目描述]
 *  给定两个由英文字母组成的字符串 String 和 Pattern，要求找到 Pattern 在 String 中第一次出现的位置，并将此位置后的 String 的子串输出。如果找不到，则输出“Not Found”。
 *  本题旨在测试各种不同的匹配算法在各种数据情况下的表现。各组测试数据特点如下：
 *  数据0：小规模字符串，测试基本正确性；
 *  数据1：随机数据，String 长度为 10^5 ，Pattern 长度为 10 ；
 *  数据2：随机数据，String 长度为 10^5 ，Pattern 长度为 10^2 ；
 *  数据3：随机数据，String 长度为 10^5 ，Pattern 长度为 10^3 ；
 *  数据4：随机数据，String 长度为 10^5 ，Pattern 长度为 10^4 ；
 *  数据5：String 长度为 10^6 ，Pattern 长度为 10^5 ；测试尾字符不匹配的情形；
 *  数据6：String 长度为 10^6 ，Pattern 长度为 10^5 ；测试首字符不匹配的情形。
 * [输入格式]
 *  输入第一行给出 String，为由英文字母组成的、长度不超过 10^6 的字符串。第二行给出一个正整数 N（≤10），为待匹配的模式串的个数。随后 N 行，每行给出一个 Pattern，
 *  为由英文字母组成的、长度不超过 10^5 的字符串。每个字符串都非空，以回车结束。
 * [输出格式]
 *  对每个 Pattern，按照题面要求输出匹配结果。
 * [输入样例]
 *  abcabcabcabcacabxy
 *  3
 *  abcabcacab
 *  cabcabcd
 *  abcabcabcabcacabxyz
 * [输出样例]
 *  abcabcacabxy
 *  Not Found
 *  Not Found
 */

#include <iostream>
#include <string>
using namespace std;

void getNextVal(string String, int nextVal[]);
int KMP(string String, string Pattern);

int main(){
    int n, i;
    string OriginalString;
    string Pattern;
    cin >> OriginalString;
    cin >> n;
    for (i = 0; i < n; i++){
        cin >> Pattern;
        int loc = KMP(OriginalString, Pattern);
        if(loc != -1) cout << OriginalString.substr(loc) << endl;
        else cout << "Not Found" << endl;
    }
    return 0;
}

void getNextVal(string String, int nextVal[]){
    int j = 0, k = -1;
    nextVal[0] = -1;
    int SLength = (int)String.size();
    while (j < SLength - 1) {
        if (k == -1 || String[j] == String[k]) {
            k++;
            j++;
            if (String[j] != String[k]) {
                nextVal[j] = k;
            } else {
                nextVal[j] = nextVal[k];
            }
        } else {
            k = nextVal[k];
        }
    }
}

int KMP(string String, string Pattern){
    int SLength = (int)String.size();
    int PLength = (int)Pattern.size();
    int nextVal[PLength];
    getNextVal(Pattern, nextVal);
    int i = 0, j = 0;
    while (i < SLength && j < PLength) {
        if (j == -1 || String[i] == Pattern[j]) {
            i++;
            j++;
        } else {
            j = nextVal[j];
        }
    }
    if (j == PLength) return (i - j);
    else return -1;
}