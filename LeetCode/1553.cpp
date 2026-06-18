/*
 * 题目：两球之间的磁力
 * 标签：二分答案 / 贪心
 * 时间复杂度：O(n log M)，M 为最大可能磁力
 * 空间复杂度：O(1)
 *
 * 题目描述：
 * 给定 n 个篮子的位置数组 position 和一个整数 m。
 * 要选 m 个篮子放入球，使得任意两球之间的 最小磁力 最大。
 * 两个球分别位于 x 和 y 时，磁力定义为 |x - y|。
 * 返回最大化的最小磁力。
 *
 * 解题思路：
 * 1. 排序篮子位置。
 * 2. 二分答案：猜测一个最小磁力 d，判断是否可选到至少 m 个篮子，
 *    使得任意相邻两球的位置差 ≥ d。
 * 3. 贪心验证：
 *    - 总是选第一个篮子放球，然后遍历后续篮子，
 *      只要当前篮子与上一个选中篮子的位置差 ≥ d，就放球。
 *    - 统计最终放球的数量。
 * 4. 二分上界：最大可能磁力不超过
 *    (max_position - min_position) / (m - 1)。
 * 5. 使用开区间二分 (left, right)，left 始终可行，
 *    right 始终不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        ranges::sort(position);

        auto check = [&](int d) -> bool {
            int cnt = 1, pre = position[0];
            for (int p : position) {
                if (p >= pre + d) {
                    ++cnt;
                    pre = p;
                }
            }
            return cnt >= m;
            };

        int l = 0;
        int r = (position.back() - position[0]) / (m - 1) + 1;

        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;
    }
};