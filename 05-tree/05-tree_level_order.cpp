/*
 * @problem: 二叉树的层序遍历 (Binary Tree Level Order Traversal)
 * @category: 树
 * @time_complexity: O(n)
 * @space_complexity: O(n)
 * @description: BFS 逐层遍历，队列存储每层节点。
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector < vector<int> ans;
        if (!root)return ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            vector<int> level;
            for (int i = 0;i < n;++i) {
                TreeNode* node = q.front(); q.pop();
                level.emplace_back(node->val);
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ans.emplace_back(std::move(level));
        }
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution s;
    auto res = s.levelOrder(root);
    for (auto& level : res) {
        for (int v : level) cout << v << " ";
        cout << endl;
    }
    return 0;
}