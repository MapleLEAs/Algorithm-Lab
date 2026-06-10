/*
 * @problem: Kruskal 最小生成树算法 (Kruskal's MST Algorithm)
 * @category: 图
 * @time_complexity: O(E log E)
 * @space_complexity: O(V)
 * @description: 并查集 + 贪心。边按权值升序排序，依次选取不形成环的边，
 *               直到选出 V-1 条边构成最小生成树。
 *               并查集判断是否成环：两顶点已在同一集合则跳过。
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//Kruskal算法实现-并查集的应用
//边类型
struct Edge {
	Edge(int s,int e,int c)
		:start(s)
		,end(e)
		,cost(c)
	{ }
	int start;
	int end;
	int cost;
};

const int SIZE = 1000;
int parent[SIZE];

int find(int val) {
	if (val == parent[val]) {
		return val;
	}
	return parent[val] = find(parent[val]);
}

int main() {
	for (int i = 0;i < SIZE;++i) {
		parent[i] = i;
	}

	vector<Edge>edges;
	int n;
	cin >> n;

	int s, e;
	int c;
	for (int i = 0;i < n;++i) {
		cin >> s >> e >> c;
		edges.emplace_back(s, e, c);
	}

	sort(edges.begin(), edges.end(),
		[](auto& a, auto& b)->bool {
			return a.cost < b.cost;
		});

	for (int i = 0;i < edges.size();++i) {
		int a = find(edges[i].start);
		int b = find(edges[i].end);
		if (a != b) {
			parent[a] = b;
			cout << edges[i].start << "->" << edges[i].end <<" "<<edges[i].cost<<endl;
		}
	}
	
}