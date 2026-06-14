/*
 * @problem: 验证二叉搜索树 (Validate Binary Search Tree)
 * @category: 树
 * @time_complexity: O(n)
 * @space_complexity: O(h)
 * @description: 递归验证。BST 要求左子树所有节点 < root，
 *               右子树所有节点 > root。用上下界限制。
 */
#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return check(root, LONG_MIN, LONG_MAX);
    }
private:
    bool check(TreeNode* node, long long lower, long long upper) {
        if (!node)return true;
        if (node->val <= lower || node->val >= upper)return false;
        return check(node->left, lower, node->val)
            && check(node->right, node->val, upper);
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(6);

    Solution s;
    cout << s.isValidBST(root) << endl;  // 0（4 < 5，右子树不合法）
    return 0;
}