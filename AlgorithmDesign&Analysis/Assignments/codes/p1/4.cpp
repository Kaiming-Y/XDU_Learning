/*
 * 使用分治算法解决：
 * You are given two sorted lists of size m and n, and are allowed unit time access to the ith element of each list.
 * Give an O(lg m + lgn) time algorithm for computing the kth largest element in the union of the two lists.
 * (For simplicity, you can assume that the elements of the two lists are distinct).
 */

#include <iostream>
#include <vector>
using namespace std;

int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
    if (nums1.size() - i > nums2.size() - j) return findKth(nums2, j, nums1, i, k);
    if (nums1.size() == i) return nums2[j + k - 1];
    if (k == 1) return min(nums1[i], nums2[j]);

    // 分别在两个数组中找到第k/2小的元素
    int si = min(i + k / 2, (int)nums1.size()), sj = j + k - si + i;
    if (nums1[si - 1] > nums2[sj - 1])
        return findKth(nums1, i, nums2, sj, k - (sj - j));
    else
        return findKth(nums1, si, nums2, j, k - (si - i));
}

int findKthLargest(vector<int>& nums1, vector<int>& nums2, int k) {
    int total = nums1.size() + nums2.size();
    if (k > total) return -1;
    return findKth(nums1, 0, nums2, 0, total - k + 1);
}

int main() {
    vector<int> nums1 = {1, 3, 5, 7, 10};
    vector<int> nums2 = {2, 4, 6, 8, 9};
    int k = 3;
    cout << "The " << k << "th largest element is " << findKthLargest(nums1, nums2, k) << endl;
    return 0;
}
