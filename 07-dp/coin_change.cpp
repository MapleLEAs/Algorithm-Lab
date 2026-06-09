/*
 * @problem: 零钱兑换 (Coin Change)
 * @category: 动态规划
 * @time_complexity: O(n * amount)
 * @space_complexity: O(amount)
 * @description: 完全背包。dp[i] = 凑出金额 i 的最少硬币数。
 *               dp[i] = min(dp[i], dp[i - coin] + 1)。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amout + 1, amount + 1);
		dp[0] = 0;
        for (int i = 1;i <= amount;++i) {
            for (auto coin : coins) {
                if (i >= coin) {
					dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
			return dp[amount] > amount ? -1 : dp[amount];
    }
};
int main() {
    Solution s;
    vector<int> coins = { 1, 2, 5 };
    cout << s.coinChange(coins, 11) << endl;  // 3
    return 0;
}