/*
 * @problem: 省份数量 (Number of Provinces)
 * @category: 图
 * @time_complexity: O(n²)
 * @space_complexity: O(n)
 * @description: 给定 n×n 邻接矩阵 isConnected，计算连通分量数。
 *               DFS 遍历未访问节点，每次 DFS 标记一个省份。
 */

#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), count = 0;
        vector<bool>vis(n, false);
        for (int i = 0;i < n;++i) {
            if (!vis[i]) {
                ++count;
                dfs(isConnected, vis, i);
            }
        }
    }
private:
    void dfs(vector<vector<int>>& isConnected, vector<bool>& vis, int i) {
        vis[i] = true;
        for (int j = 0;j < isConnected.size();++j) {
            if(isConnected[i][j] == 1 && !vis[j]) {
                dfs(isConnected, vis, j);
			}
        }
    }


};
int main() {
    Solution s;
    vector<vector<int>> m = { {1,1,0},{1,1,0},{0,0,1} };
    cout << s.findCircleNum(m) << endl;  // 2
    return 0;
}