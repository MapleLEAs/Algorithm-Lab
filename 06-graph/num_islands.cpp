/*
 * @problem: 岛屿数量 (Number of Islands)
 * @category: 图
 * @time_complexity: O(m * n)
 * @space_complexity: O(m * n)（递归栈）
 * @description: DFS 遍历网格，遇到陆地 '1' 则计数+1并沉没整个岛。
 *               沉没法：将访问过的陆地改为 '0'，省去 vis 数组。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++count;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }
};

int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    Solution s;
    cout << s.numIslands(grid) << endl;  // 3
    return 0;
}