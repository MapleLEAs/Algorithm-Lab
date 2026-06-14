/*
 * @problem: 最长回文子串 (Longest Palindromic Substring)
 * @category: 动态规划
 * @time_complexity: O(n²)
 * @space_complexity: O(1)
 * @description: 中心扩展法。每个字符和每两个字符之间作为中心，
 *               向两边扩展找最长回文。
 */

#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, maxLen = 0;
        for (int i = 0; i < s.size(); i++) {
            int len1 = expand(s, i, i);      // 奇数长度
            int len2 = expand(s, i, i + 1);  // 偶数长度
            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, maxLen);
    }

private:
    int expand(const string& s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--; r++;
        }
        return r - l - 1;
    }
};

int main() {
    Solution s;
    cout << s.longestPalindrome("babad") << endl;  // bab 或 aba
    return 0;
}