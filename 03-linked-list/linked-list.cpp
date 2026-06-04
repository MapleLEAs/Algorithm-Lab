/*
 * @problem: 反转链表 (Reverse Linked List)
 * @category: 链表
 * @time_complexity: O(n)
 * @space_complexity: O(1)
 * @description: 迭代法反转单链表，三指针 prev/curr/next
*/
struct Node {
	int val_;
	Node* next;
	Node(int val) : val_(val), next(nullptr) {}
};

class LinkedList {
private:
	Node* head_;
public:
	LinkedList() :head_(nullptr) {}
	void reverse() {
        Node* prev = nullptr;
        Node* curr = head_;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;   // ① 先保存下一个节点
            curr->next = prev;   // ② 反转当前节点的指针
            prev = curr;         // ③ prev 前进
            curr = next;         // ④ curr 前进
        }
        head_ = prev;            // ⑤ 最后更新头节点
	}
};
