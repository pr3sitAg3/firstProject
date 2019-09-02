#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#define MAX 1000001
#define VMAX 1000000000

using namespace std;
/*RunTime: O((V+E)logV)*/
typedef pair<int, int> PII;
void dijkastra(vector<PII> adj[], int n, int src, vector<long long>& d){
    priority_queue<PII, vector<PII>, greater<PII>> q;
    int visited[MAX] = {0};
    d[src] = 0;
    q.push(make_pair(0, src));
    while(!q.empty()){
        PII u = q.top();
        // cout<<"MinSrc="<<u.second<<" And weight="<<u.first<<endl;
        q.pop();
        src = u.second;
        // int y;
        //y = u.first;
        if(visited[src])
            continue;
        visited[src] = 1;
        for(int i =0; i<adj[src].size(); i++){
            PII xt = adj[src][i];
            // cout<<"Src="<<src<<" and Tgt="<<xt.second<<" and dist[first]="
            //         <<u.first << " and dist[second]="<<d[xt.second]<<endl;
            if( d[src]+ xt.first < d[xt.second]){
                // cout<<"Src="<<src<<" and Tgt="<<xt.second<<endl;
                d[xt.second] = d[src]+xt.first;
                q.push(make_pair(d[xt.second], xt.second));
            }
        }
    }
}

int main() {
	int n,m;
	cin >> n >> m;
	vector<PII> adj[MAX];
	for(int i=0; i<m; i++){
	    int a, b, w;
	    cin >> a >> b>> w;
	    adj[a].push_back(make_pair(w, b));
	   // adj[b].push_back(make_pair(w, a));
	}
	vector<long long> dist(MAX, VMAX);
	dijkastra(adj, n, 1, dist);
	for(int i=2; i<=n; i++){
	    int tx =  (dist[i]==0)?(pow(10,9)):dist[i];
	    cout<<tx<< " ";
	}
	return 0;
}

