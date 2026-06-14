/*
 * @problem: 每日温度 (Daily Temperatures)
 * @category: 栈
 * @time_complexity: O(n)
 * @space_complexity: O(n)
 * @description: 单调递减栈。栈中存索引。遍历时若当前温度 > 栈顶温度，
 *               弹出栈顶，当前索引 - 栈顶索引 = 等待天数。
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        vector<int> ans(n, 0);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && T[i] > T[st.top()]) {
                int prev = st.top(); st.pop();
                ans[prev] = i - prev;
            }
            st.push(i);
        }
        return ans;
    }
};

int main() {
    vector<int> t = { 73,74,75,71,69,72,76,73 };
    Solution s;
    auto ans = s.dailyTemperatures(t);
    for (int x : ans) cout << x << " ";
    cout << endl;  // 1 1 4 2 1 1 0 0
    return 0;
}