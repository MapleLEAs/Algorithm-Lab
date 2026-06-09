/*
 * @problem: 对称二叉树 (Symmetric Tree)
 * @category: 树
 * @time_complexity: O(n)
 * @space_complexity: O(h)
 * @description: 递归比较左子树的左节点和右子树的右节点，
 *               以及左子树的右节点和右子树的左节点。
 */

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
	}
private:
    bool check(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        return p->val == q->val
            && check(p->left, q->right)
            && check(p->right, q->left);
    }

};
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); root->right = new TreeNode(2);
    root->left->left = new TreeNode(3); root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4); root->right->right = new TreeNode(3);

    Solution s;
    cout << s.isSymmetric(root) << endl;  // 1
    return 0;
}