/*
3399. 字符相同的最短子字符串 II
困难
给你一个长度为 n 的二进制字符串 s 和一个整数 numOps。
你可以对 s 执行以下操作，最多 numOps 次：

   选择任意下标 i（其中 0 <= i < n），并 翻转 s[i]，即如果 s[i] == '1'，则将 s[i] 改为 '0'，反之亦然。

你需要 最小化 s 的最长 相同 子字符串 的长度，相同子字符串是指子字符串中的所有字符都相同。

返回执行所有操作后可获得的 最小 长度。
*/


/*
思路:对于本题因为子串长度越长，越能在 numOps 次操作内完成，有单调性。这意味着如果可以把每段子串的长度都变成至多为 m，那么也可以变成至多为 m + 1, m + 2, … 如果不能把每段子串的长度都变成至多为 m，那么也不能变成至多为 m−1, m−2, …

二分长度的上界 m，问题变成：
判断能否在 numOps 次操作内，把每段连续相同子串的长度都变成 ≤m 的。
考虑其中一段连续相同子串要怎么改，最少要改多少次。
*/


class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();
        /*
        二分答案两种情况:
        第一种m==1时0101...或1010
        第二种直接计算每一段相同字符需要的操作次数
        */
        auto check = [&](int mid)->bool {
            int cnt = 0;
            if (mid == 1) {
                for (int i = 0;i < n;++i) {
                    cnt += (s[i] ^ i) & 1;
                }
                cnt = min(cnt, n - cnt);//cnt是0101...,n-cnt是1010...
            }
            else {
                int k = 0;
                for (int i = 0;i < n;i++) {
                    k++;
                    if (i == n - 1 || s[i + 1] != s[i]) {
                        cnt += k / (mid + 1);
                        k = 0;
                    }
                }
            }
            return cnt <= numOps;
            };
        //二分答案的左右边界
        int l = 1, r = n;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }
};