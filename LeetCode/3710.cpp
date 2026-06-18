/*
 * 题目：最大分区因子（二分图判定 + 二分答案）
 * 标签：二分答案 / DFS 染色 / 二分图
 * 时间复杂度：O(n² × log M)，M 为最大曼哈顿距离
 * 空间复杂度：O(n)
 *
 * 题目描述：
 * 给定平面上 n 个点 points，其中 points[i] = [x, y]。
 * 定义两点 (xi, yi) 和 (xj, yj) 的"冲突距离"为
 * |xi - xj| + |yi - yj|。你需要找到一个最大整数 L，使得
 * 可以将所有点分成两部分，并且任意同一部分内两点之间的
 * 冲突距离都 ≥ L。换句话说，距离 < L 的两个点必须分在
 * 不同部分。
 *
 * 解题思路：
 * 1. 特殊判断：
 *    - n == 1：无法分成两部分，返回 -1。
 *    - n == 2：只有两个点，无论如何分都不会有同组冲突，返回 0。
 * 2. 二分答案：
 *    - 二分 L，判断在距离 < L 的点必须分在不同组的情况下，
 *      能否将图二分染色。
 *    - 左边界 l = 0，右边界 r = max_distance + 1。
 * 3. 二分图判定（DFS 染色）：
 *    - 建图：如果两点距离 < L，则它们之间有一条边。
 *    - 用 1 和 -1 对点染色，相邻点必须不同色。
 *    - 如果染色冲突（相邻点同色），说明不是二分图，L 不可行。
 *    - 使用 int8_t 存储颜色以节省内存。
 *    - 使用 C++23 的显式对象参数 (this auto&& dfs) 实现递归 lambda。
 * 4. 二分上界：计算所有点对的最大曼哈顿距离 + 1。
 * 5. 开区间二分：left 可行，right 不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();

        // 特殊情况处理
        if (n == 1) return -1;
        if (n == 2) return 0;

        // 检查能否在阈值为 low 时完成二分染色
        auto check = [&](int low) -> bool {
            vector<int8_t> colors(n, 0);  // 0: 未染色, 1: 颜色1, -1: 颜色2

            auto dfs = [&](this auto&& dfs, int x, int8_t c) -> bool {
                colors[x] = c;
                auto& p = points[x];
                for (int y = 0; y < n; ++y) {
                    auto& q = points[y];
                    // 跳过自身以及距离 ≥ low 的点
                    if (y == x || abs(p[0] - q[0]) + abs(p[1] - q[1]) >= low) {
                        continue;
                    }
                    // 相邻点同色 或 未染色但递归染色失败 → 不是二分图
                    if (colors[y] == c || (colors[y] == 0 && !dfs(y, -c))) {
                        return false;
                    }
                }
                return true;
                };

            // 遍历所有连通分量
            for (int i = 0; i < n; ++i) {
                if (colors[i] == 0 && !dfs(i, 1)) {
                    return false;
                }
            }
            return true;
            };

        // 计算最大曼哈顿距离作为二分上界
        int max_dis = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                max_dis = max(max_dis,
                    abs(points[i][0] - points[j][0]) +
                    abs(points[i][1] - points[j][1]));
            }
        }

        // 开区间二分：left 可行，right 不可行
        int l = 0, r = max_dis + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;
    }
};