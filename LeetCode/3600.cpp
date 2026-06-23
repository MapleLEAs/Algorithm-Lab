/*
 * 题目：最大化生成树的最小边强度
 * 标签：并查集 / 最小生成树 / 贪心
 * 时间复杂度：O(E log E + E * α(N))
 * 空间复杂度：O(N)
 *
 * 题目描述：
 * 给定 n 个节点和若干条边 edges，每条边包含 [u, v, strength, must]。
 * strength 表示边的强度，must=1 表示该边必须保留且不能升级。
 * 你需要保留恰好 n-1 条边构成一个生成树，其中 must=1 的边必须全部包含。
 * 你有 k 次升级机会，每次升级可以将一条 must=0 的边的强度翻倍，
 * 每条可升级边最多升级一次。
 * 定义生成树的稳定性为所有保留边中的最小强度。
 * 求所有有效生成树可能达到的最大稳定性。
 * 如果无法形成生成树则返回 -1。
 *
 * 解题思路：
 * 1. 建立两个并查集：
 *    - uf：只包含 must=1 的边，用于构建必须边的连通分量。
 *    - all_uf：包含所有边，用于判断全图是否连通。
 * 2. 处理必须边：
 *    - 遍历所有 must=1 的边，合并 uf。
 *    - 如果两条必须边形成环，则无法构成生成树，返回 -1。
 *    - 记录必须边的最小强度 min_must。
 * 3. 判断全图连通性：
 *    - 用 all_uf 合并所有边，如果不连通返回 -1。
 *    - 如果 uf 已经连通（必须边已构成生成树），直接返回 min_must。
 * 4. 贪心处理非必须边：
 *    - 将所有边按强度降序排序。
 *    - 依次用非必须边合并 uf，补全生成树。
 *    - 收集补全过程中使用的边的强度到数组 extra。
 * 5. 升级策略：
 *    - 基础答案为 min(min_must, 2 * extra.back())，
 *      即必须边最小值和额外边最小值（翻倍前）的较小者。
 *    - 如果有升级机会 (k < extra.size())，可以选择跳过
 *      extra 中靠后的某条边，将其翻倍后可能不再是瓶颈，
 *      答案为 min(ans, extra[m - 1 - k])。
 */
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
using namespace std;

class UnionFind {
    vector<int> fa;
public:
    int cc;  // 连通分量数

    UnionFind(int n) : fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    bool merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x == y) return false;
        fa[x] = y;
        --cc;
        return true;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        UnionFind uf(n);       // 只含必须边的并查集
        UnionFind all_uf(n);   // 含所有边的并查集
        int min_must = INT_MAX;

        // 1. 处理必须边
        for (auto& e : edges) {
            int must = e[3], s = e[2];
            if (must) {
                if (!uf.merge(e[0], e[1])) return -1;  // 必须边成环
                min_must = min(min_must, s);
            }
            all_uf.merge(e[0], e[1]);
        }

        // 2. 检查全图连通性
        if (all_uf.cc > 1) return -1;
        if (uf.cc == 1) return min_must;

        // 3. 按强度降序排序
        ranges::sort(edges, {}, [](auto& e) { return -e[2]; });

        // 4. 贪心选择非必须边补全生成树
        vector<int> extra;
        for (auto& e : edges) {
            int must = e[3], s = e[2];
            if (!must && uf.merge(e[0], e[1])) {
                extra.push_back(s);
            }
        }

        // 5. 计算答案
        int m = extra.size();
        int ans = min(min_must, extra[m - 1] * 2);
        if (k < m) {
            ans = min(ans, extra[m - 1 - k]);
        }
        return ans;
    }
};