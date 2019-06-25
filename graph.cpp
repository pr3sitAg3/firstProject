#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void bfs(vector<int> adj[], int n, int source){
/*Breadth First Search */
	if (source>n || source<1)	return;
	int visited[n+1]={0};
	queue<int> q;
	visited[source]=1;
	q.push(source)	;
	while(!q.empty()){
		int t = q.front();
		q.pop();
		for(int i=0; i<adj[t].size(); i++){
			if(!visited[adj[t][i]]) {
				q.push(adj[t][i]);	
				visited[adj[t][i]]=1;
			}
		}
		cout<<t<<" ";
	}
}

void displayGraph(vector<int> adjList[], int n){
	for(int i = 1;i <= n;++i)
    {   
            cout << "Adjacency list of node " << i << ": ";
        for(int j = 0;j < adjList[i].size();++j)
            {
            if(j == adjList[i].size() - 1)
                    cout << adjList[i][j] << endl;
            else
                cout << adjList[i][j] << " --> ";
    }
    }
}
int main(){
	int n,e;
	cin >> n >>e;	
//	adjList
	vector<int> adjList[n+1];
	for(int i=1; i<=e; i++){
		int x,y;
		cin >> x >> y;
		if(x<=n && y<=n){
			adjList[x].push_back(y);
			adjList[y].push_back(x);
		}
		else	cout<<"Invalid Edge"<<endl;
	}
	displayGraph(adjList, n);
	bfs(adjList,n, 1);
	return 0;
}
