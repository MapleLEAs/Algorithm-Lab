/*
 * @problem: 二叉树的前序遍历 (Binary Tree Preorder Traversal)
 * @category: 树
 * @time_complexity: O(n)
 * @space_complexity: O(h)，h 为树高
 * @description: 根→左→右，递归 + 迭代两种方式
 */

#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
	Node(int v) : val(v), left(nullptr), right(nullptr) {};
	int val;
	Node* left;
	Node* right;
};
class Solution {
public:
	// 前序遍历递归
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ans;
		dfs(root, ans);
		return ans;
	}

	//栈迭代
	vector<int> preorderIterative(TreeNode* root) {
		stack<TreeNode*> s;
		vector<int> ans;
		if (!root)return ans;
		s.push(root);
		while(!s.empty()) {
			TreeNode* node = s.top();
			s.pop();
			ans.push_back(node->val);
			if (node->right) s.push(node->right);//右子树先入栈，保证左子树先访问
			if (node->left) s.push(node->left);//左子树后入栈，保证左子树先访问
		}
		return ans;
	}
	

private:
	//前序遍历递归接口
	void dfs(TreeNode* root, vector<int>& res) {
		if (!root) return;
		res.push_back(root->val);
		dfs(root->left, res);
		dfs(root->right, res);
	}
};