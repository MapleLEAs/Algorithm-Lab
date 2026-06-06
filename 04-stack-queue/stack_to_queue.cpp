/*
 * @problem: 用栈实现队列 (Implement Queue using Stacks)
 * @category: 栈
 * @time_complexity: push O(1)，pop 均摊 O(1)
 * @space_complexity: O(n)
 * @description: 两个栈模拟队列，一个负责入队，一个负责出队。
 *               出队时若出队栈为空，将入队栈全部倒入出队栈。
 */

#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
    stack<int> inStack, outStack;

    void transfer() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }

public:
    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        transfer();
        int val = outStack.top();
        outStack.pop();
        return val;
    }

    int peek() {
        transfer();
        return outStack.top();
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << q.peek() << endl;  // 1
    cout << q.pop() << endl;   // 1
    cout << q.empty() << endl; // 0
    return 0;
}