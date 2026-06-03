/*
 * @problem: 3399. 字符相同的最短子字符串 II (Shortest Substring With Same Character II)
 * @category: 二分搜索
 * @time_complexity: O(n log n)
 * @space_complexity: O(1)
 * @description:
 * 给你一个长度为 n 的二进制字符串 s 和一个整数 numOps。
 * 最多 numOps 次翻转操作（0变1，1变0），目标是让最长连续相同子串的长度尽可能小。
 *
 * 核心思路：二分答案 + 贪心检验
 *
 * 1. 单调性：如果能把最长连续相同子串长度变成 ≤ m，那 ≤ m+1 也一定能做到。
 *    所以可以二分这个最小的 m。
 *
 * 2. 检验函数 check(mid)：
 *    - m == 1 的特殊情况：
 *      目标是变成 0101... 或 1010... 交替串。
 *      计算变成这两种模式分别需要多少次翻转，取 min。
 *      cnt = 与 0101... 不同的位置数，n-cnt 就是与 1010... 不同的位置数。
 *    - m > 1 的情况：
 *      遍历每一段连续相同字符，长度为 k。
 *      要把这段拆成每段长度 ≤ m，最少需要在其中插入"分隔符"（翻转某些位置）。
 *      每 m+1 个字符就需要改 1 个，所以这段需要 k/(m+1) 次操作。
 *      所有段的操作次数累加。
 *
 * 3. 二分边界：l = 1, r = n，找到最小的满足 check(mid) == true 的 mid。
 */

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();

        auto check = [&](int mid) -> bool {
            int cnt = 0;
            if (mid == 1) {
                // 特殊处理：目标是最长相同子串长度 = 1，即必须是 0101... 或 1010...
                for (int i = 0; i < n; ++i) {
                    cnt += (s[i] ^ i) & 1;  // 与 0101... 模式不同的位数
                }
                cnt = min(cnt, n - cnt);    // 取 0101... 和 1010... 中改动较少的那种
            }
            else {
                int k = 0;  // 当前连续相同段的长度
                for (int i = 0; i < n; i++) {
                    k++;
                    if (i == n - 1 || s[i + 1] != s[i]) {  // 一段结束了
                        cnt += k / (mid + 1);  // 每 mid+1 个需要改 1 个
                        k = 0;
                    }
                }
            }
            return cnt <= numOps;
            };

        int l = 1, r = n;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                r = mid - 1;  // 能行，试试更小的
            }
            else {
                l = mid + 1;  // 不行，试试更大的
            }
        }
        return l;
    }
};

/*
 * 示例 1：
 * 输入：s = "000001", numOps = 1
 * 输出：2
 * 解释：翻转 s[2] 得 "001001"，最长连续相同子串长度 = 2
 *
 * 示例 2：
 * 输入：s = "0000", numOps = 2
 * 输出：1
 * 解释：翻转 2 个位置得 "0101"，最长连续相同子串长度 = 1
 *
 * 示例 3：
 * 输入：s = "0101", numOps = 0
 * 输出：1
 * 解释：已经是交替串，不需要操作
 */