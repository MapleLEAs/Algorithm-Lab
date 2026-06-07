/*
 * @problem: 有效的括号 (Valid Parentheses)
 * @category: 栈
 * @time_complexity: O(n)
 * @space_complexity: O(n)
 * @description: 用栈匹配括号对，左括号入栈，右括号检查栈顶是否匹配。
 */

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        for (char c : s) {
            if (pairs.count(c)) {
                if (stk.empty() || stk.top() != pairs[c]) {
                    return false;
                }
                stk.pop();
            }
            else {
				stk.push(c);
            }
        }
        return stk.empty();
    }
};
int main() {
    Solution s;
    cout << s.isValid("()[]{}") << endl;  // 1
    cout << s.isValid("(]") << endl;      // 0
    return 0;
}