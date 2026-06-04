/*
 * @problem: 最长公共子序列 (Longest Common Subsequence)
 * @category: 动态规划
 * @time_complexity: O(m * n)
 * @space_complexity: O(m * n)
 * @description: dp[i][j] 表示 text1[0..i-1] 与 text2[0..j-1] 的 LCS 长度
 *               text1[i-1] == text2[j-1] → dp[i][j] = dp[i-1][j-1] + 1
 *               text1[i-1] != text2[j-1] → dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
		int m = size(text1), n = size(text2);
        vector<vector<int>>dp(m+1, vector<int>(n+1, 0));
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else {
                   dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};
int main() {
    Solution s;
    cout << s.longestCommonSubsequence("abcde", "ace") << endl;
    return 0;
}