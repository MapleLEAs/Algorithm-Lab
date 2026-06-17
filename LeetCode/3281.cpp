/*
 * 题目：最大化区间选点的最小间距
 * 标签：二分答案 / 贪心
 * 时间复杂度：O(n log M)，M 为最大可能间距
 * 空间复杂度：O(1)
 *
 * 题目描述：
 * 给定一个整数数组 start 和一个非负整数 d。
 * 对于每个 start[i]，可以在 [start[i], start[i] + d] 区间内任选一个整数作为该位置的点。
 * 定义 score 为所有已选点之间相邻差的最小值。
 * 在最优选择下，求 score 的最大可能值。
 *
 * 解题思路：
 * 1. 排序 start 数组，保证从左到右处理。
 * 2. 二分答案：猜测一个最小间距 score，判断是否可行。
 * 3. 贪心验证：
 *    - 维护上一个选点的位置 x（初始为 -∞）。
 *    - 对于每个区间 [s, s+d]：
 *      · 当前点至少应选在 max(x + score, s) 的位置（保证间距 ≥ score）。
 *      · 如果该位置超过 s+d，说明无法满足当前间距，返回 false。
 *    - 所有区间都能成功选点则返回 true。
 * 4. 二分上界：理论上最大最小间距不会超过 (max_start + d - min_start) / (n - 1)。
 * 5. 使用开区间二分 (left, right)，left 始终可行，right 始终不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxPossibleScore(vector<int>& start, int d) {
        ranges::sort(start);

        auto check = [&](int score) -> bool {
            long long x = LLONG_MIN;  // 上一个选点的位置
            for (int s : start) {
                x = max(x + score, (long long)s);
                if (x > s + d) {
                    return false;
                }
            }
            return true;
            };

        int n = start.size();
        int left = 0;
        int right = (start.back() + d - start[0]) / (n - 1) + 1;

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};