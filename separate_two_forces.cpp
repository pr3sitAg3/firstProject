#include<iostream>
using namespace std;
/*
This Program separate out two type of values
in either side i.e. negative on left end and
positive on right end.
*/
int main(){
  int n; 
  //input size of array
	cin >> n;
	int arr[n];
  //input element of array
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
	/*Debug output
  cout << "\nbefore \n";
	for(int i=0; i<n; i++){
		cout << arr[i] <<",";
	}
  */
	for(int i=1; i<n; i++){
		int k = i;
		for(int j=i-1;j>=0;j--){
			if(arr[k] < arr[j] and ((arr[k]<0 && arr[j]>0) || (arr[k]>0 && arr[j]<0)) and k>0){
				int temp = arr[k];
				arr[k] = arr[j];
				arr[j]= temp;
				k--;
			}
			else
				break;
		}
	}
	cout << "\nSeparated Values:\n";
	for(int i=0; i<n; i++){
		cout << arr[i] <<",";
	}
	return 0;
}
