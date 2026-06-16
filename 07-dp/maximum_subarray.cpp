/*
 * 题目：最大子数组和
 * 标签：动态规划 / Kadane 算法
 * 时间复杂度：O(n)，空间复杂度：O(1)
 * 思路：cur 表示以当前位置结尾的最大子数组和。
 *       如果 cur < 0，说明前面的和是负的，丢弃，从当前重新开始。
 *       每步更新全局最大值 ans。
 */
#include <vector>
#include <algorithm>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int cur = 0, ans = nums[0];
    for (int x : nums) {
        cur = max(cur + x, x);
        ans = max(ans, cur);
    }
    return ans;
}