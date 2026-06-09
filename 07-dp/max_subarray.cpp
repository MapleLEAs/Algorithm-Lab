/*
 * @problem: 最大子数组和 (Maximum Subarray)
 * @category: 动态规划
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: Kadane 算法。dp[i] = max(dp[i-1] + nums[i], nums[i])，
 *               即要么接在前面子数组后面，要么自己单开。
 *               滚动优化为 cur = max(cur + nums[i], nums[i])。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur= 0, ans = nums[0];
        for (int i = 0;i < nums.size();++i) {
            cur = max(cur + nums[i], nums[i]);
            ans = max(ans, cur);
        }
        return ans;
    }
};
int main() {
    Solution s;
    vector<int> nums = { -2,1,-3,4,-1,2,1,-5,4 };
    cout << s.maxSubArray(nums) << endl;  // 6
    return 0;
}