/*
 * 2.3-7
 * 请给出一个运行时间为ʘ(nlgn)的算法，使之能在给定一个由n个整数构成的集合S和另一个整数x时，判断出S中是否存在有两个其和等于x的元素
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool hasPairWithSum(const std::vector<int>& S, int x) {

    vector<int> sortedS = S;
    sort(sortedS.begin(), sortedS.end());

    int left = 0;
    int right = (int)sortedS.size() - 1;

    while (left < right) {
        int sum = sortedS[left] + sortedS[right];
        if (sum == x) {
            return true;
        } else if (sum < x) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}

int main() {
    // n个整数构成的集合S
    vector<int> S = {1, 2, 3, 4, 5};
    // 整数x
    int x = 10;

    if (hasPairWithSum(S, x)) {
        cout << "exist" << endl;
    } else {
        cout << "not exist" << endl;
    }

    return 0;
}

