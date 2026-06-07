/*
 * @problem: 打家劫舍 (House Robber)
 * @category: 动态规划
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: dp[i] = max(dp[i-1], dp[i-2] + nums[i])，
 *               滚动数组优化为两个变量。
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        int first = nums[0], secord = max(nums[0], nums[1]);
        for (int i = 2;i < (int)nums.size();++i) {
            int temp = max(first+nums[i],secord);
            first = secord;
            secord = temp;
        }
        return secord;
    }

};
int main() {
    Solution s;
    vector<int> nums = { 2,7,9,3,1 };
    cout << s.rob(nums) << endl;  // 12
    return 0;
}