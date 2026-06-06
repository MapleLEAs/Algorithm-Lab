/*
 * @problem: 环形链表 (Linked List Cycle)
 * @category: 链表
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: 快慢指针，快指针一次两步，慢指针一步。
 *               若相遇则有环，快指针到达 nullptr 则无环。
 */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head_) {
        ListNode* slow = head_, * fast = head_;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    int posCycle(ListNode* head_) {
        int pos = 0;
        ListNode* slow = head_, * fast = head_;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                fast = head_;
                while (fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                    pos++;
                }
                return pos;
            }
        }
        return -1;
    }
};

int main() {
    // 测试1：有环链表
    {
        ListNode* head = new ListNode(3);
        ListNode* n2 = new ListNode(2);
        ListNode* n0 = new ListNode(0);
        ListNode* n4 = new ListNode(-4);
        head->next = n2;
        n2->next = n0;
        n0->next = n4;
        n4->next = n2;  // 环入口在位置 1

        Solution s;
        assert(s.hasCycle(head) == true);
        assert(s.detectCycle(head) == 1);
        cout << "[1] has cycle, entry pos=1 PASSED" << endl;
    }

    // 测试2：无环链表
    {
        ListNode* head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        Solution s;
        assert(s.hasCycle(head) == false);
        assert(s.detectCycle(head) == -1);
        cout << "[2] no cycle PASSED" << endl;
    }

    // 测试3：单节点无环
    {
        ListNode* head = new ListNode(1);
        Solution s;
        assert(s.hasCycle(head) == false);
        assert(s.detectCycle(head) == -1);
        cout << "[3] single node no cycle PASSED" << endl;
    }

    // 测试4：单节点自环
    {
        ListNode* head = new ListNode(1);
        head->next = head;  // 自己指向自己
        Solution s;
        assert(s.hasCycle(head) == true);
        assert(s.detectCycle(head) == 0);
        cout << "[4] single node self cycle PASSED" << endl;
    }

    cout << "all pass" << endl;
    return 0;
}