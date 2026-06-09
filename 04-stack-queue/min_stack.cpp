/*
 * @problem: 最小栈 (Min Stack)
 * @category: 栈
 * @time_complexity: O(1) 每次操作
 * @space_complexity: O(n)
 * @description: 两个栈，一个存数据，一个存当前最小值。
 *               push 时同时更新 minStack；pop 时两个一起弹出。
 */

#include <iostream>
#include <stack>
using namespace std;
class Solution {
private:
    stack<int>data, minStack;
public:
    void push(int val) {
        data.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
		}
        void pop() {
            if (data.top() == minStack.top()) minStack.pop();
            data.pop();
        }

        int top() { return data.top(); }
        int getMin() { return minStack.top(); }
    }
};

int main() {
    MinStack s;
    s.push(-2); s.push(0); s.push(-3);
    cout << s.getMin() << endl;  // -3
    s.pop();
    cout << s.top() << endl;     // 0
    cout << s.getMin() << endl;  // -2
    return 0;
}