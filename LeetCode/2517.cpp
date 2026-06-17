/*
 * 题目：礼盒的最大甜蜜度
 * 标签：二分答案 / 贪心
 * 时间复杂度：O(n log M)，M 为最大可能甜蜜度
 * 空间复杂度：O(1)
 *
 * 题目描述：
 * 给定一个整数数组 price 表示若干糖果的价格，和一个整数 k。
 * 要从中选择 k 个糖果组成一个礼盒，礼盒的 甜蜜度 定义为所选糖果中
 * 任意相邻价格差的最小值。求可以获得的 最大甜蜜度。
 *
 * 解题思路：
 * 1. 排序价格数组。
 * 2. 二分答案：猜测一个甜蜜度 d，判断是否可选到至少 k 个糖果，
 *    使得任意相邻两糖果的价格差 ≥ d。
 * 3. 贪心验证：
 *    - 总是贪心地选择第一个糖果，然后遍历价格数组，
 *      只要当前价格与上一个选中的价格之差 ≥ d，就选中它。
 *    - 统计最终选中的糖果数量。
 * 4. 二分上界：最大可能甜蜜度不超过
 *    (max_price - min_price) / (k - 1)。
 * 5. 使用开区间二分 (left, right)，left 始终可行，
 *    right 始终不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        ranges::sort(price);

        auto check = [&](int d) -> int {
            int cnt = 1, pre = price[0];
            for (int p : price) {
                if (p - pre >= d) {
                    ++cnt;
                    pre = p;
                }
            }
            return cnt;
            };

        int l = 0;
        int r = (price.back() - price[0]) / (k - 1) + 1;

        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) >= k ? l : r) = mid;
        }
        return l;
    }
};