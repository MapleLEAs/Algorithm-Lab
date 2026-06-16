/*
 * 题目：合并 K 个升序链表
 * 标签：链表 / 最小堆
 * 时间复杂度：O(N log K)，空间复杂度：O(K)
 * 思路：将每个链表的头节点放入最小堆。
 *       每次弹出堆顶（当前最小节点），接到结果链表中。
 *       如果弹出的节点有 next，则将其 next 入堆。
 */
#include <vector>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
        };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    for (ListNode* head : lists) {
        if (head) pq.push(head);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node;
        tail = node;
        if (node->next) pq.push(node->next);
    }
    return dummy.next;
}