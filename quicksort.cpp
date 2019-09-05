#include <iostream>
#include <cmath>
using namespace std;
typedef unsigned long long int ll;
void swap(ll & a, ll & b){
    ll temp = a;
    a = b;
    b = temp;
}
int partition(ll arr[], int start, int end){
    ll pivot = arr[start];
    int i = start;
    for(int j=i+1; j<=end; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[start]);
    return i;
}
int randPartition(ll arr[], int start, int end){
    ll random = start+ rand()%(end-start+1);
    swap(arr[start], arr[random]);
    return partition(arr, start, end);
}
void display(ll arr[], int start, int end){
    for(int i=start; i<=end; i++){
        cout<< arr[i]<<" ";
    }
    cout<<endl;
}
void quicksort(ll arr[], int start, int end){
    if(start<end){
        // cout<<"Start:"<<start<<",End:"<<end;
        int i = randPartition(arr, start, end);
        // cout<<"Partitioned index: "<<i<<endl;
        // display(arr, start, end);
        quicksort(arr, start, i-1);
        quicksort(arr, i+1, end);
        // cout<<"Returning Start:"<<start<<",End:"<< end << endl;
    }
}

int main() {
	int n;
	cin >> n;					
	ll arr[n];
	for(int i=0; i<n; i++)
	    cin >> arr[i];
// 	cout << "Start--------------"<<endl;
// 	display(arr, n);
	quicksort(arr, 0, n-1);
// 	cout << endl<<"end--------------"<<endl;
	display(arr, 0, n-1);
    return 0; 
}
