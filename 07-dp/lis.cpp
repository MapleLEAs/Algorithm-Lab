/*
 * @problem: 最长递增子序列 (Longest Increasing Subsequence)
 * @category: 动态规划
 * @time_complexity: O(n log n)
 * @space_complexity: O(n)
 * @description: 贪心 + 二分。维护数组 tails，tails[i] 表示长度为 i+1 的
 *               LIS 的最小尾元素。遍历时二分查找插入位置。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>num) {
        vector<int> tails;
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end())
                tails.push_back(x);
            else
                *it = x;
        }
        return tails.size();
    }
};
int main() {
    vector<int> nums = { 10,9,2,5,3,7,101,18 };
    Solution s;
    cout << s.lengthOfLIS(nums) << endl;  // 4
    return 0;
}