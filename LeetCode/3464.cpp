/*
 * 题目：正方形边界上 k 个点的最大最小间距
 * 标签：二分答案 / 贪心 / 一维展开
 * 时间复杂度：O(n² log S)，S 为正方形周长
 * 空间复杂度：O(n)
 *
 * 题目描述：
 * 给定一个边长为 side 的正方形，以及正方形边界上的 n 个点 points。
 * points[i] = [x, y] 表示点在边界上的坐标。
 * 你需要从这些点中选出 k 个点，使得任意两点之间的 最短距离 最大化。
 * 距离定义为两点在正方形边界上的 曼哈顿路径距离（即沿边界行走的最短距离）。
 * 返回最大化的最小距离。
 *
 * 解题思路：
 * 1. 边界展开（一维化）：
 *    - 将正方形边界按顺时针展开成一条直线，总长度为 4 * side。
 *    - 底边 (y=0)：坐标映射为 x
 *    - 右边 (x=side)：坐标映射为 side + y
 *    - 顶边 (y=side)：坐标映射为 3*side - x
 *    - 左边 (x=0)：坐标映射为 4*side - y
 *    - 排序后得到一维坐标数组 a。
 * 2. 二分答案：
 *    - 二分最小间距 low，判断能否选到 k 个点满足要求。
 *    - 左边界 left = 1，右边界 right = 周长 / k + 1。
 * 3. 贪心验证（环形枚举起点）：
 *    - 因为边界是环形的，需要枚举每个点作为起点 start。
 *    - 窗口范围：[start, start + 周长 - low]
 *    - 在窗口内贪心选点：每次选距离上一个选中点 ≥ low 的最近点。
 *    - 如果能选满 k 个点，则 low 可行。
 *    - 使用二分查找 lower_bound 加速找下一个点。
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        // 1. 边界展开：二维坐标 → 一维顺时针长度
        vector<long long> a;
        for (auto& p : points) {
            int x = p[0], y = p[1];
            if (x == 0) {
                a.push_back(y);                      // 左边：从 (0,0) 向上
            }
            else if (y == side) {
                a.push_back(side + x);               // 顶边：从左到右
            }
            else if (x == side) {
                a.push_back(side * 3LL - y);         // 右边：从上到下
            }
            else {
                a.push_back(side * 4LL - x);         // 底边：从右到左
            }
        }
        ranges::sort(a);

        // 2. 检查能否在间距 ≥ low 的情况下选出 k 个点
        auto check = [&](int low) -> bool {
            for (long long start : a) {
                long long end = start + side * 4LL - low;  // 环形窗口有效范围
                long long cur = start;

                // 贪心选 k-1 个后续点
                for (int i = 0; i < k - 1; ++i) {
                    auto it = ranges::lower_bound(a, cur + low);
                    if (it == a.end() || *it > end) {
                        cur = -1;  // 选不够 k 个
                        break;
                    }
                    cur = *it;
                }
                if (cur >= 0) return true;  // 成功选满
            }
            return false;
            };

        // 3. 开区间二分
        int left = 1;
        int right = side * 4LL / k + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};