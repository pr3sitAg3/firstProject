

#include <iostream>
#include <vector>

using namespace std;
void buildSegTree(int a[], int t[], int node, int start, int end){
    if(start == end){
        t[node] = a[start];
    }
    else{
        int mid = (start+end)/2;
        buildSegTree(a,t,2*node, start, mid);
        buildSegTree(a,t, 2*node +1, mid+1, end);
        int left=2*node, right=2*node+1;
        t[node] = (t[left]< t[right])?t[left]:t[right];
    }
}

void update(int a[], int t[],int node, int start, int end, int idx, int val ){
    if(start == end){
        a[idx] = val;
        t[node] = val;
    }
    else{
        int mid = (start+end)/2 ;
        if(start <= idx && idx <= mid){
            update(a,t,2*node, start, mid, idx, val);
        }
        else{
            update(a,t, 2*node +1, mid+1, end, idx, val);
        }
        int left = 2*node;
        int right = left+1;
        t[node] = (t[left]< t[right])?t[left]:t[right];
    }
}
int query(int t[], int node, int start, int end, int l, int r){
    if(r < start ||  end < l){
        return 9999999;
    }
    if(l<= start and r>= end){
        return t[node];
    }
    int mid = (start+end)/2;
    int p1 = query(t, 2*node, start, mid, l, r);
    int p2 = query(t, 2*node+1, mid+1, end, l, r);
    return ((p1<p2)?p1:p2);
}
int main() {
	int n,t;
	cin >> n >> t;
	int arr[100005], tree[2000005];
	for(int i=1; i<=n; i++){
	    cin >> arr[i];
	}
	buildSegTree(arr, tree, 1, 1, n);
// 	for(int i=1; i<2*n; i++){
// 	    cout<<"tree["<<i<<"]="<<tree[i]<<endl;
// 	}
    while(t--){
        char qtype;
        int x, y ;
        cin >> qtype >> x>>y;
        switch(qtype){
            case 'q':
                cout<<query(tree,1,1,n,x,y)<<endl;
                break;
            case 'u':
                update(arr,tree,1,1,n,x,y);
                break;
        }
    }
    return 0;
}
