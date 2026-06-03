#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<queue>
using namespace std;

/*
设计数据结构:
vertics	        :图的邻接表，索引从 1 开始（vertics[0] 是空占位符）
Vertic.data_	:顶点的数据（从文件读取的一行字符串）
Vertic.adjust	:邻接表，存储该顶点所有出边的目标顶点编号
*/
class Digraph {
public:
	/*从文件中读取图的结构
	data.txt 格式:
		A
		2 4 5
		B
		6
		C
		2 4
		...
		奇数行	A、B、C...	顶点名称
		偶数行	2 4 5、6...	该顶点的邻接顶点编号
		
		读取步骤
		先插入空顶点：vertics.emplace_back("") → 索引 0 占位，让真实顶点从 1 开始编号。
		循环读取：
		读一行 → 去掉换行符 → 作为顶点名存入 vertics.back().data_。
		读下一行 → 用 strtok 按空格和逗号分割 → 转成整数 → 存入 vertics.back().adjust。
		*/
	void readFile(const string& filename) {
		// 这里可以添加读取文件的逻辑，构建图的结构
		FILE* file = fopen(filename.c_str(), "r");
		if (file == nullptr) {
			throw runtime_error("无法打开文件");
		}

		vertics.emplace_back("");

		while(!feof(file)) {
			char line[1024] = { 0 };
			fgets(line, sizeof(line), file);
			string linestr(line);
			vertics.emplace_back(linestr.substr(0, linestr.find('\n')));
			fgets(line, sizeof(line), file);
			char* token = strtok(line, " ,");
			while(token != nullptr) {
				int adjIndex = atoi(token);
				vertics.back().adjust.push_back(adjIndex);
				token = strtok(nullptr, " ,");
			}
		}
		fclose(file);
	}
	//测试输出邻接表
	void printAdjacencyList() {
		for (size_t i = 1; i < vertics.size(); ++i) {
			cout << "Vertex " << i << ": " << vertics[i].data_ << " -> ";
			for (int adj : vertics[i].adjust) {
				cout << adj << " ";
			}
			cout << endl;
		}
	}
	//深度优先搜索:前序遍历
	void dfs() {
		vector<bool>vis(vertics.size(), false);
		dfs(1, vis);
	}
	//广度优先搜索:层序遍历
	void bfs() {
		vector<bool> vis(vertics.size(), false);
		queue<int> q;
		q.push(1);
		vis[1] = true;
		while (!q.empty()) {
			int index = q.front();
			q.pop();
			cout << "Visited Vertex " << index << ": " << vertics[index].data_ << endl;
			for (int adj : vertics[index].adjust) {
				if (!vis[adj]) {
					q.push(adj);
					vis[adj] = true;
				}
			}
		}
	}
	//最短路径:使用 BFS 找到 start 到 end 的最短路径
	void shortPath(int start, int end) {
		vector<bool> vis(vertics.size(), false);// 记录访问状态
		vector<int> prev(vertics.size(), -1);// 记录路径，prev[i] 存储访问 i 的前一个顶点
		queue<int> q;// BFS 队列
		q.push(start);
		vis[start] = true;
		while (!q.empty()) {
			int index = q.front();
			q.pop();
			if (index == end) {
				break;
			}
			for (int adj : vertics[index].adjust) {
				if (!vis[adj]) {
					q.push(adj);
					vis[adj] = true;
					prev[adj] = index;
				}
			}
		}
		if (!vis[end]) {
			cout << "No path from " << start << " to " << end << endl;
			return;
		}
		vector<int> path;
		for (int at = end; at != -1; at = prev[at]) {
			path.push_back(at);
		}
		reverse(path.begin(), path.end());
		cout << "Shortest path from " << start << " to " << end << ": ";
		for (int v : path) {
			cout << v << " ";
		}
		cout << endl;
	}
private:
	//DFS 辅助函数
	void dfs(int index, vector<bool>& vis) {
		if (index <= 0 || index >= vertics.size() || vis[index]) {
			return;
		}
		vis[index] = true;
		cout << "Visited Vertex " << index << ": " << vertics[index].data_ << endl;
		for (int adj : vertics[index].adjust) {
			dfs(adj, vis);
		}
	}
private:
	//图的邻接表，索引从 1 开始（vertics[0] 是空占位符）
	struct Vertic {
		Vertic(string data)
			:data_(data)
			{}
		string data_;
		list<int>adjust;
	};
private:
	//存储图的顶点
	vector<Vertic>vertics;
};

int main() {
	Digraph graph;
	try {
		graph.readFile("data.txt");
		graph.printAdjacencyList();
	}
	catch (const exception& e) {
		cerr << "错误: " << e.what() << endl;
	}
	cout << "------------------------" << endl;
	graph.dfs();
	cout << "------------------------" << endl;
	graph.bfs();
	cout << "------------------------" << endl;
	graph.shortPath(1, 8);
	return 0;
}