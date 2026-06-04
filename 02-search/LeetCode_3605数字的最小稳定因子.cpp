/*
 * @problem: 最小稳定子数组长度 (Min Stable Subarray Length)
 * @category: 二分查找
 * @time_complexity: O(n * log n * log V)，V 为数组最大值
 * @space_complexity: O(log V)
 * @description:
 * 给定数组 nums 和最多删除次数 maxC。
 * 目标是最小化"最长稳定子数组"的长度。
 * 稳定子数组 = 子数组内所有元素的 GCD > 1。
 *
 * 核心思路：
 * 1. 二分答案：子数组长度 mid 是否可行
 * 2. check(mid)：贪心扫描，维护当前段的所有后缀 GCD
 *    - 后缀 GCD 只会减少，且最多有 O(log V) 种不同值
 *    - 用 vector<pair<gcd, 起点索引>> 压缩存储
 * 3. 当段长度 > mid 且 GCD 仍 = 1，需要切断一次（消耗 maxC）
 * 4. 消耗完 maxC 还切不断 → 不可行
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();

        auto check = [&](int mid) -> bool {
            vector<pair<int, int>> intervals;  // {gcd, 起始索引}
            int c = maxC;

            for (int i = 0; i < n; ++i) {
                int x = nums[i];

                // 更新所有后缀的 GCD
                for (auto& [g, _] : intervals) {
                    g = gcd(g, x);
                }
                intervals.emplace_back(x, i);  // 自己单独一段

                // 去重：相同 GCD 只保留最靠右的
                int idx = 1;
                for (int j = 1; j < intervals.size(); ++j) {
                    if (intervals[j].first != intervals[j - 1].first) {
                        intervals[idx++] = intervals[j];
                    }
                }
                intervals.resize(idx);

                // 去除 GCD = 1 的
                if (!intervals.empty() && intervals[0].first == 1) {
                    intervals.erase(intervals.begin());
                }

                // 当前段长度超过 mid，需要切断
                if (!intervals.empty() && i - intervals[0].second + 1 > mid) {
                    if (c == 0) return false;  // 没次数了
                    --c;
                    intervals.clear();  // 重新开始一段
                }
            }
            return true;
            };

        int l = -1, r = n / (maxC + 1);
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r;
    }
};