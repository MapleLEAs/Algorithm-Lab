/*
 * 题目：省份数量
 * 标签：并查集 / DFS
 * 时间复杂度：O(n²)，空间复杂度：O(n)
 * 思路：用并查集维护连通分量。
 *       遍历矩阵上三角，isConnected[i][j]==1 时合并 i 和 j。
 *       最后统计 parent[i] == i 的根节点个数。
 */
#include <vector>
using namespace std;

/*
 * 题目：省份数量
 * 标签：并查集 / DFS
 * 时间复杂度：O(n²)，空间复杂度：O(n)
 * 思路：用并查集维护连通分量。
 *       遍历矩阵上三角，isConnected[i][j]==1 时合并 i 和 j。
 *       最后统计 parent[i] == i 的根节点个数。
 */
#include <vector>
using namespace std;

class Solution {
    vector<int> parent;

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int a, int b) {
        parent[find(a)] = find(b);
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) merge(i, j);
            }
        }

        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == i) ++cnt;
        }
        return cnt;
    }
};