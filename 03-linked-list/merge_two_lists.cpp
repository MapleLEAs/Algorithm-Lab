/*
 * @problem: 合并两个有序链表 (Merge Two Sorted Lists)
 * @category: 链表
 * @time_complexity: O(m + n)
 * @space_complexity: O(1)
 * @description: 双指针遍历两个链表，每次取较小节点接到新链表尾部。
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(0), * cur = dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->neext;
			cur->next = l1 ? l1 : l2;
        }
		return dummy->next;
    }
};

int main() {
    ListNode* l1 = new ListNode(1); l1->next = new ListNode(3);
    ListNode* l2 = new ListNode(2); l2->next = new ListNode(4);

    Solution s;
    ListNode* merged = s.mergeTwoLists(l1, l2);
    for (auto p = merged; p; p = p->next) cout << p->val << " ";
    cout << endl;  // 1 2 3 4
    return 0;
}