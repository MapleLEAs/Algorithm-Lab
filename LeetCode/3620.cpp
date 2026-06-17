/*
 * 题目：在限制边权下寻找最短路径的最大可能最小边权
 * 标签：二分答案 / DFS 记忆化搜索 / 图论
 * 时间复杂度：O((V + E) * log W)，W 为边权最大值
 * 空间复杂度：O(V + E)
 *
 * 题目描述：
 * 给定一个带权无向图 edges，其中 edges[i] = [u, v, w] 表示节点 u 和 v 之间
 * 有一条权值为 w 的边。数组 online 标记每个节点是否在线（可用）。
 * 只有两个端点都在线的边才能通行。节点 0 始终在线。
 * 要求从节点 0 走到节点 n-1，路径总长度（边权和）不能超过 k。
 * 在满足总路径长度 ≤ k 的前提下，最大化路径中 最小边权 的值。
 * 如果无法到达，返回 -1；如果不存在边权的限制则返回最大可能的边权。
 *
 * 解题思路：
 * 1. 建图：仅保留两端都在线的边，同时记录以节点 0 为端点的最大边权。
 * 2. 二分答案：猜测一个最小边权下限 lower，判断在只走 ≥ lower 的边的情况下，
 *    从 0 到 n-1 的最短路径长度是否 ≤ k。
 * 3. DFS 记忆化搜索：
 *    - memo[x] 表示从节点 x 到终点 n-1 的最短路径长度。
 *    - 每次只走权值 ≥ lower 的边。
 *    - 使用 C++23 的显式对象参数 (this auto&& dfs) 实现递归 lambda。
 * 4. 二分上下界：left = -1 表示无解（所有边都可用时仍超 k），
 *    right = max_weight_of_node_0 + 1 为不可能更大的上限。
 * 5. 使用开区间二分 (left, right)，left 始终可行，right 始终不可行，最终返回 left。
 */
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        vector<vector<pair<int, int>>> g(n);
        int max_w0 = -1;

        // 建图：只保留两端都在线的边
        for (auto& e : edges) {
            int x = e[0], y = e[1], wt = e[2];
            if (online[x] && online[y]) {
                g[x].emplace_back(y, wt);
                if (x == 0) {
                    max_w0 = max(max_w0, wt);
                }
            }
        }

        vector<long long> memo(n);

        // 检查在只走 ≥ lower 的边的情况下，最短路径是否 ≤ k
        auto check = [&](int lower) -> bool {
            ranges::fill(memo, -1);

            auto dfs = [&](this auto&& dfs, int x) -> long long {
                if (x == n - 1) return 0;

                auto& res = memo[x];
                if (res != -1) return res;

                res = LLONG_MAX / 2;  // 防止加法溢出
                for (auto& [y, wt] : g[x]) {
                    if (wt >= lower) {
                        res = min(res, dfs(y) + wt);
                    }
                }
                return res;
                };

            return dfs(0) <= k;
            };

        // 开区间二分：left 可行，right 不可行
        int l = -1, r = max_w0 + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;
    }
};