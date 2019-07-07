#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    long cbt, index;
} Node;
void displayheap(vector<Node> & heap){
    int n= heap.size();
    for(int i=0; i<n; i++){
        cout<<"element:index="<<heap[i].index<<",val="<<heap[i].cbt<<endl;
    }
}
void insert(vector<Node> & heap, int idx, int ct){
    Node t;
    t.index = idx; t.cbt = ct;
    heap.push_back(t);
    int n = heap.size();
    //cout<<"Inside Insert-size:"<<n<<endl;
    if(n==1){
        return;
    }
    int curr = n-1;
    int par = curr/2;
    while(curr>0){
        if(heap[curr].cbt < heap[par].cbt){
            //cout<<"Swap"<<endl;
            Node temp = heap[curr];
            heap[curr] = heap[par];
            heap[par] = temp;
            // cout<<"Node:index="<<heap[curr].index<<",val="<<heap[curr].cbt<<endl;
            curr = par;
            par = par/2;
        }
        else
            break;
    }
}
int pop(vector<Node>& heap) {
    Node x = heap[0];
    int n = heap.size();
    heap[0] = heap[n-1];
    heap.pop_back();
    n = n-1;
    int curr = 0;
    int l_child = 2*curr+1 , r_child = 2*curr+2;
    while(l_child < n ){
        if(heap[l_child].cbt < heap[curr].cbt){
            if(r_child < n && heap[r_child].cbt < heap[l_child].cbt ){
                Node temp = heap[curr];
                heap[curr] =  heap[r_child];
                heap[r_child] = temp;
                curr = r_child;
            }
            else{
                Node temp = heap[curr];
                heap[curr] =  heap[l_child];
                heap[l_child] = temp;
                curr = l_child;
            }
        }
        else if(heap[l_child].cbt == heap[curr].cbt) {
            if(r_child < n && heap[r_child].cbt < heap[curr].cbt ){
                Node temp = heap[curr];
                heap[curr] =  heap[r_child];
                heap[r_child] = temp;
                curr = r_child;
            }
            else{
                break;
            }
        }
        else{
            if(r_child < n && heap[r_child].cbt < heap[curr].cbt ){
                Node temp = heap[curr];
                heap[curr] =  heap[r_child];
                heap[r_child] = temp;
                curr = r_child;
            }
            else{
                break;
            }
        }
        l_child = 2*curr + 1;
        r_child = l_child +1;
    }
    return x.index;
}

void arraySort(vector<vector<int>> &arr){
    int n = arr.size();
    if(n <=1){
        return;
    }
    for(int i=1; i<n; i++){
        int k = i;
        for(int j= i-1; j>=0 && k>0; j--){
            if(arr[k][0] < arr[j][0]){
                long t1 = arr[k][0], t2 = arr[k][1];
                arr[k][0] = arr[j][0];  arr[k][1]=arr[j][1];
                arr[j][0] = t1; arr[j][1] = t2;
                k--;
            }
            else
                break;
        }
    }
    // for(int i=0; i<n; i++){
    //     cout<<"index:"<<arr[i][0]<<",val:"<<arr[i][1]<<endl;
    // }
}

long long minimumAverage(vector<vector<int>> customers) {
    vector<Node> heap;
    int n = customers.size();
    // cout<<"CustomerSize="<<n<<endl;
    arraySort(customers);   //sort customers on the basis of Arrival Time
    long long wtime=0, ctime=0, elapsedtime=0;
    wtime = customers[0][1];
    ctime = elapsedtime = customers[0][1]+customers[0][0];
    // cout<<wtime << ctime <<elapsedtime<<endl;
    for(int i=1; i<n; i++){
        // cout<<"Iteration:"<<i<<endl;
        // cout<<"heap size="<<heap.size()<<endl;
        // cout<<"waiting time="<<wtime<<endl;
        if(ctime >= customers[i][0]){
            insert(heap, i, customers[i][1]);
            // displayheap(heap);
        }
        else{
            while(heap.size()!=0){
                int temp = pop(heap);
                ctime += customers[temp][1] ;
                wtime += abs(ctime - customers[temp][0]);
            }
            insert(heap, i, customers[i][1]);
        }
        // cout<<"Iteration:"<<i<<" Ends"<<endl;
    }
    while(heap.size()!=0){
        int temp = pop(heap);
        ctime += customers[temp][1] ;
        wtime += abs(ctime - customers[temp][0]);
    } 
    //cout<<wtime/n<<endl; 
    return wtime/n ; 
}

int main()
{
    int n;
    cin >> n;
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> customers(n);
    for (int customers_row_itr = 0; customers_row_itr < n; customers_row_itr++) {
        customers[customers_row_itr].resize(2);

        for (int customers_column_itr = 0; customers_column_itr < 2; customers_column_itr++) {
            cin >> customers[customers_row_itr][customers_column_itr];
        }

  //      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long long result = minimumAverage(customers);

    cout << result << "\n";
    return 0;
}
