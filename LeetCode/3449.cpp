/*
 * 题目：最大化游戏分数的最小值
 * 标签：二分答案 / 贪心
 * 时间复杂度：O(n log M)，M 为最大可能分数
 * 空间复杂度：O(1)
 *
 * 题目描述：
 * 给定长度为 n 的数组 points 和整数 m。
 * 初始时 gameScore[i] = 0，从下标 -1 出发。
 * 每次操作可以右移或左移，并将移动后所在位置的 points[i] 加到
 * gameScore[i] 上。第一次移动后下标必须在数组范围内。
 * 求至多 m 次操作后，gameScore 中最小值的最大可能值。
 *
 * 解题思路：
 * 1. 二分答案：
 *    - 二分猜测最小值 mid，判断能否在 m 次操作内使所有
 *      gameScore[i] ≥ mid。
 *    - 左边界 l = 0（无需操作），右边界为最乐观估计 + 1。
 * 2. 移动转化（横跳模型）：
 *    - 任何复杂移动都可转化为在相邻位置间反复横跳。
 *    - 让位置 i 被访问 k 次，需要的操作次数为 2k - 1：
 *      1 次前进到达 i，后续 k-1 次横跳各需 2 步。
 *    - 同时，这 k-1 次横跳也让位置 i+1 顺带被访问了 k-1 次。
 * 3. 贪心验证：
 *    - 遍历每个位置 i，计算需要新增的访问次数 k。
 *    - pre 记录位置 i 已被顺带访问的次数。
 *    - k = ceil(mid / points[i]) - pre。
 *    - 如果 i 是最后一个位置且 k ≤ 0，提前结束。
 *    - 每次至少访问 1 次（k = max(k, 1)）。
 *    - 消耗操作次数：res -= 2k - 1。
 *    - 更新 pre = k - 1 给下一个位置。
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        auto check = [&](long long mid) -> bool {
            int n = points.size();
            int res = m;      // 剩余操作次数
            int pre = 0;      // 当前位置已被顺带访问的次数

            for (int i = 0; i < n; ++i) {
                // 需要新增的访问次数
                int k = (mid - 1) / points[i] + 1 - pre;

                // 最后一个位置已达标，无需继续
                if (i == n - 1 && k <= 0) break;

                k = max(k, 1);          // 至少访问 1 次
                res -= k * 2 - 1;       // 消耗操作次数
                if (res < 0) return false;

                pre = k - 1;            // 顺带访问次数传递给下一位置
            }
            return true;
            };

        // 开区间二分
        long long l = 0;
        long long r = 1LL * (m + 1) / 2 * ranges::min(points) + 1;
        while (l + 1 < r) {
            long long mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;
    }
};