/*
 * @problem: 爬楼梯 (Climbing Stairs)
 * @category: 动态规划
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: dp[i] = dp[i-1] + dp[i-2]，
 *               滚动数组优化为两个变量。
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n < 2)return n;
        int a = 1, b = 2;
        for (int i = 3; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};

int main() {
    Solution s;
    cout << s.climbStairs(5) << endl;  // 8
    return 0;
}