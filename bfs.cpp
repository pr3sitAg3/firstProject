#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#define N 5
using namespace std;

void displayGraph(vector<vector<int> > g) {
	int r = g.size();
	int c = g[0].size();
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
}
void bfs(int s, vector<vector<int> > g, vector<int>& par, vector<int>& dist) {
	int r = N;
	enum code
	{
		white, grey, black
	};
	//cout << "white="<<white <<", grey="<< grey <<", black="<< black<<endl;

	int arr[N] = { white };
	queue<int> q;
	arr[s] = grey;
	par[s] = -1;
	dist[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		for (int i = g[t].size()-1; i >=0 ; i--) {
			if (g[t][i] && arr[i] == white) {
				arr[i] == grey;
				par[i] = t;
				dist[i] = dist[t] + 1;
				q.push(i);
			}
			//if (g[t][i] && arr[i] == black) {
				//cout << "Cycle Detected --> at:" << i + 1 << endl;
			//}
		}
		arr[t] = black;
	}
}
int main() {
	cout << "Program started" << endl;
	vector<vector<int> > graph(N, vector<int>(N, 0));
	int n, e;
	cout << "Enter node and edge" << endl;
	cin >> n >> e;
	n = n % N;
	e = e % (N * N);
	//undirected graph
	for (int i = 0; i < e; i++) {
		int u, v;
		cin >> u >> v;
		u = u > 0 ? u - 1 : u;
		v = v > 0 ? v - 1 : v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}
	displayGraph(graph);
	vector<int> par(N, INT_MAX);
	vector<int> dist(N, INT_MAX);
	bfs(0, graph, par, dist);
	for (int i = 0; i < par.size(); i++) {
		cout << par[i] << " ";
	}
	cout << endl;
	return 0;
}
