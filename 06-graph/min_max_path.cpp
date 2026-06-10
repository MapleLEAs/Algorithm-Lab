/*
 * @problem: 最小化最大边权路径 (Minimize Maximum Edge Weight Path)
 * @category: 图
 * @time_complexity: O(E log E)
 * @space_complexity: O(V)
 * @description: Kruskal 变体。边按权值升序排序，依次合并，
 *               当起点 s 和终点 t 首次连通时，当前边的权值
 *               即为路径上最大边权的最小值。
 */
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Road {
	Road(int a, int b, int c)
		:s(a)
		, v(b)
		, w(c)
	{
	}
	int s;
	int v;
	int w;
};
const int SIZE = 10005;
int parent[SIZE];


int find(int val) {
	if (val == parent[val]) {
		return val;
	}
	return parent[val] = find(parent[val]);
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[x] = y;
	}
}
int main() {

	for (int i = 0;i < SIZE;++i) {
		parent[i] = i;
	}
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	vector<Road>roads;
	int u, v, w;
	for (int i = 0;i < m;++i) {
		cin >> u >> v >> w;
		roads.emplace_back(u, v, w);
	}

	sort(roads.begin(), roads.end(),
		[](auto& a, auto& b)->bool {
			return a.w < b.w;
		});
	for (int i = 0;i < roads.size();++i) {
		merge(roads[i].s, roads[i].v);
		if (find(s) == find(t)) {
			cout << roads[i].w << endl;
			break;
		}
	}


	return 0;
}