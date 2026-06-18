/*
 * 题目：最大安全系数
 * 标签：多源 BFS / 并查集 / 二分答案
 * 时间复杂度：O(n² log n)
 * 空间复杂度：O(n²)
 *
 * 题目描述：
 * 给定一个 n×n 的网格 grid，其中 grid[i][j] = 1 表示该格子有小偷，
 * grid[i][j] = 0 表示空格子。定义格子 (i,j) 的安全系数为该格子到
 * 最近小偷的曼哈顿距离。你需要从 (0,0) 走到 (n-1,n-1)，
 * 路径的安全系数定义为路径上所有格子安全系数的最小值。
 * 求所有可能路径中，安全系数的最大值。
 *
 * 解题思路：
 * 1. 多源 BFS 分层：
 *    - 将所有小偷位置作为起点，同时向外扩散。
 *    - dis[i][j] 记录格子 (i,j) 到最近小偷的距离。
 *    - groups[level] 存储所有距离为 level 的格子坐标。
 * 2. 并查集倒序合并：
 *    - 从安全系数最高的层开始（groups.size()-2），逐层降低。
 *    - 对于当前层 groups[ans] 中的每个格子，
 *      将其与四周距离 ≥ 自身距离的格子合并（表示可以安全通行）。
 *    - 每次合并后检查 (0,0) 和 (n-1,n-1) 是否连通。
 *    - 如果连通，当前安全系数 ans 就是答案。
 * 3. 为什么倒序？
 *    - 从高安全系数到低安全系数合并，能保证第一次连通时的
 *      安全系数就是所有可行路径中的最大值。
 * 4. 边界情况：
 *    - 如果起点或终点就是小偷（dis[0][0]=0），答案直接为 0。
 */
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

class Solution {
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> q;
        vector<vector<int>> dis(n, vector<int>(n, -1));

        // 初始化：所有小偷位置入队，距离为 0
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    q.emplace_back(i, j);
                    dis[i][j] = 0;
                }
            }
        }

        // 多源 BFS 分层：按距离记录每一层的格子
        vector<vector<pair<int, int>>> groups = { q };
        while (!q.empty()) {
            vector<pair<int, int>> nq;
            for (auto& [i, j] : q) {
                for (auto& d : dirs) {
                    int x = i + d[0], y = j + d[1];
                    if (0 <= x && x < n && 0 <= y && y < n && dis[x][y] < 0) {
                        nq.emplace_back(x, y);
                        dis[x][y] = groups.size();  // 当前距离 = 层编号
                    }
                }
            }
            groups.push_back(nq);
            q = move(nq);
        }

        // 并查集初始化
        vector<int> fa(n * n);
        iota(fa.begin(), fa.end(), 0);
        function<int(int)> find = [&](int x) -> int {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
            };

        // 从高安全系数倒序合并
        for (int ans = (int)groups.size() - 2; ans > 0; ans--) {
            for (auto& [i, j] : groups[ans]) {
                // 与四周距离 ≥ 自身的格子合并
                for (auto& d : dirs) {
                    int x = i + d[0], y = j + d[1];
                    if (0 <= x && x < n && 0 <= y && y < n
                        && dis[x][y] >= dis[i][j]) {
                        fa[find(x * n + y)] = find(i * n + j);
                    }
                }
            }
            // 检查起点和终点是否连通
            if (find(0) == find(n * n - 1)) {
                return ans;
            }
        }
        return 0;
    }
};