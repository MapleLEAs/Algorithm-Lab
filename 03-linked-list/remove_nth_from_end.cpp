/*
 * @problem: 删除链表的倒数第 N 个节点 (Remove Nth Node From End of List)
 * @category: 链表
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: 快慢指针。快指针先走 n 步，然后快慢一起走。
 *               快指针到末尾时，慢指针在倒数第 n+1 个位置，删除其 next。
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        for (int i = 0; i <= n; i++) fast = fast->next;

        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy.next;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution s;
    auto* res = s.removeNthFromEnd(head, 2);
    for (auto* p = res; p; p = p->next) cout << p->val << " ";
    cout << endl;  // 1 2 3 5
    return 0;
}