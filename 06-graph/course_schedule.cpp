/*
 * @problem: 课程表 (Course Schedule)
 * @category: 图
 * @time_complexity: O(V + E)
 * @space_complexity: O(V + E)
 * @description: BFS 拓扑排序，维护入度数组，
 *               入度为 0 入队，出队时减少依赖课程的入度。
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        for (auto pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }

        queue <int>p;
        for (int i = 0;i < numCourses;++i) {
            if (indegree[i] == 0) {
                p.push(i);
            }
        }
        int taken = 0;
        while (!p.empty()) {
            int course = p.front();
            p.pop();
            taken++;
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    p.push(next);
                }
            }
        }
        return taken == numCourses;
    }
};
int main() {
    Solution s;
    vector<vector<int>> pre = { {1,0},{2,1},{3,2} };
    cout << s.canFinish(4, pre) << endl;  // 1
    return 0;
}