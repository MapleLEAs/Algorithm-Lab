/*
 * 题目：最大化城市的最小供电量
 * 标签：二分答案 / 贪心 / 差分数组
 * 时间复杂度：O(n log M)，M 为最大可能电量
 * 空间复杂度：O(n)
 *
 * 题目描述：
 * 给定 n 座城市的初始供电站数量 stations，每个供电站覆盖半径为 r。
 * 即第 i 座城市的初始电量为 stations[i-r..i+r] 之和。
 * 你可以额外新建最多 k 个供电站，每个新建的供电站同样覆盖半径 r。
 * 求所有城市中最小电量的最大可能值。
 *
 * 解题思路：
 * 1. 前缀和预处理：
 *    - 用前缀和快速计算每座城市的初始电量 power[i]。
 *    - 同时记录所有城市的最小电量 mn。
 * 2. 二分答案：
 *    - 猜测目标电量 low，判断能否通过新建 ≤ k 个供电站使所有城市达标。
 *    - 左边界 left = mn + k/n（最保守估计），右边界 right = mn + k + 1。
 * 3. 贪心验证（差分数组）：
 *    - diff[i] 记录在位置 i 处电量的变化量。
 *    - sum_d 累积当前城市获得的额外电量。
 *    - 遍历每座城市：
 *      · 若当前总电量 = power[i] + sum_d ≥ low，跳过。
 *      · 否则计算需补充的电量 m = low - (power[i] + sum_d)。
 *      · 在 i + r 处新建 m 个供电站（贪心，覆盖最远）。
 *      · 用差分数组 diff 更新影响范围 [i, i+2r] 的电量变化。
 *    - 新建总数超过 k 则不可行。
 * 4. 开区间二分：left 可行，right 不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();

        // 前缀和：快速计算区间电量
        vector<long long> sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + stations[i];
        }

        // 计算每座城市的初始电量，记录最小值
        vector<long long> power(n);
        long long mn = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            power[i] = sum[min(i + r + 1, n)] - sum[max(i - r, 0)];
            mn = min(mn, power[i]);
        }

        // 检查能否让所有城市电量 ≥ low
        auto check = [&](long long low) -> bool {
            vector<long long> diff(n + 1, 0);  // 差分数组
            long long sum_d = 0;                // 累计额外电量
            long long built = 0;                // 已新建供电站数

            for (int i = 0; i < n; ++i) {
                sum_d += diff[i];
                long long m = low - (power[i] + sum_d);  // 还缺多少
                if (m <= 0) continue;

                built += m;
                if (built > k) return false;

                sum_d += m;  // 新增电量立即生效
                diff[min(i + r * 2 + 1, n)] -= m;  // 影响范围结束
            }
            return true;
            };

        // 开区间二分
        long long left = mn + k / n;       // 最保守下界
        long long right = mn + k + 1;      // 最大可能上界 + 1
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};