/*
 * @problem: 二叉树的最大深度 (Maximum Depth of Binary Tree)
 * @category: 树
 * @time_complexity: O(n)
 * @space_complexity: O(h)
 * @description: DFS，树的最大深度 = max(左子树深度, 右子树深度) + 1。
 */

#include <iostream>
#include <algorithm>
using namespace std;

class TreeNode {
    public:
    int val;
    TreeNode* left;
    TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution s;
    cout << s.maxDepth(root) << endl;  // 3
    return 0;
}