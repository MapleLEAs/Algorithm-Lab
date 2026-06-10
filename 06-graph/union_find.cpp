/*
 * @problem: 并查集 (Union Find / Disjoint Set Union)
 * @category: 图
 * @time_complexity: 查找 O(α(n)) ≈ O(1)，合并 O(α(n))
 * @space_complexity: O(n)
 * @description: 并查集维护不相交集合的合并与查询。
 *               路径压缩：查找时把节点直接指向根，加速后续查找。
 *               按秩合并：将矮树合并到高树下，保持树平衡。
 */
#include<iostream>
using namespace std;
const  int SIZE = 9;
int parent[SIZE];
int rank_[SIZE];


//// Find the root of a node
//int find(int val) {
//	int ans = val;
//	while(parent[ans] != ans) {
//		ans = parent[ans];
//	}
//	parent[val] = ans; // Path compression optimization
//	return ans;
//}
// 查找根节点（路径压缩）
int rfind(int val) {
	if (parent[val] == val) {
		return val;
	}
	else {
		parent[val]= rfind(parent[val]);
		return parent[val];// 路径压缩
	}
}

// 合并两个集合（按秩合并）
void merge(int a, int b) {
	int x = rfind(a);
	int y = rfind(b);
	if (x != y) {
		if (rank_[x] <= rank_[y]) {//按秩合并
			if (rank_[x] == rank_[y]) {
				++rank_[x];
			}
			parent[x] = y;
		}
		else {
			parent[y] = x; 
		}
		
	}
}
int main() {
	
	for (int i = 0;i < SIZE;++i) {
		rank_[i] = 1;
	}
	// Initialize the parent array
	for (int i = 0;i < SIZE;++i) {
		parent[i] = i;
	}
	int v1, v2;
	for (int i = 0;i < SIZE - 1;++i) {
		cin >> v1 >> v2;
		merge(v1, v2);
	}
	cout << (rfind(1) == rfind(2) ? "1 and 2 are in the same set" : "1 and 2 are in different sets") << endl;

}