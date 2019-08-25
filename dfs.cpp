#include<iostream>
#include<vector>
#include<stack>
#include<climits>
#define N 50
using namespace std;

enum {
	white,
	grey,
	black
};
class graph {
private:
	int nodes, time;
	
public:
	int par[N], d[N], f[N];
	vector<int> g[N];
	graph(int n) {
		nodes = n > 100 ? N : n;
		time = 0;
		for (int i = 0; i < nodes; i++) {
			par[i] = -1;
			d[i] = 0;
			f[i] = 0;
		}
	}
	void dfs_util(int, int[]);
	void addEdge(int, int);
	void dfs();
	void display();
};
void graph::display() {
	cout<<"Graph has Node = "<<nodes << endl;
	for(int i=0; i<nodes; i++){
		cout<<"Node "<<i<<" --> ";
		int l = g[i].size();
		for(int j=0; j<l; j++)
			cout<<g[i][j]<<" ";
		cout<<endl;
	}
	for (int i = 0; i < nodes; i++) {
		cout << "Node[" << i << "] has Parent[" << par[i] << "] StartAt["
			<< d[i] << "] EndAt[" << f[i] << "]." << endl;
	}
}
void graph::dfs() {
	int visited[nodes] = { white };
	for (int i = 0; i < nodes; i++) {
		if (visited[i] == white)
			par[i] = i;
			dfs_util(i, visited);
	}
}
void graph::dfs_util(int src, int visited[]) {
	stack<int> s;
	s.push(src);
	cout<<"(";
	visited[src] = grey;
	d[src] = time;
	while (!s.empty()) {
		int u = s.top();
//		s.pop();
//		cout<<"Discover Adj for Vertex:"<<u<<"-->"<<endl;
		int flag=0;//to check when to pop element from stack[when all the descendent of u are traversed]
		for (int i = g[u].size() - 1; i >= 0 && visited[u]!=black; i--) {
			if (visited[g[u][i]] == white) {
				time++;
//				cout<<"New discovered Vertex:"<<g[u][i]<<" at time: "<<time<<"// ";
				visited[g[u][i]] = grey;
				d[g[u][i]] = time;
				par[g[u][i]] = u;
				s.push(g[u][i]);
				flag=1;
				cout<<"(";
			}
		}
		if(flag==1){
			visited[u] = black;
//			cout<<endl;
		}
		else{
			s.pop();
			cout<<")";
			time++; 
			f[u] = time;
		}
	}
}
void graph::addEdge(int u, int v) {
	if (u < nodes && v < nodes) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
}
/*
Application of DFS
1. Detect cycle in a Graph
2. Find connected component
3. check if Graph is strongly connected
*/

int main() {
	int n, e;
	graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.dfs();
//	g.display();
	return 0;
}
