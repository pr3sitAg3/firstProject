#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void display(vector<int> v){
     int n = v.size();
     for(int i=0; i<n; i++)
        cout<<"v["<<i<<"]="<<v[i]<<endl;
    cout<<"End of Display"<<endl;
}

void displayHashTable(vector<int> ht[], int size){
    for(int i=0; i<size; i++){
        int l = ht[i].size();
        for(int j=0; j<l; j++ ){
            cout<<ht[i][j]<<" ";
        }
        cout<<endl;
    }

}
/*
In every ith iteration if divisible by ith prime number stack the number in ith index
in hash table.
*/
vector<int> waiter(vector<int> number, int q) {
    vector<int> prime(1201,-1);
    // cout<<"Q="<<q<<endl;
    int p_count =0;
    for(int i=2; p_count<1201; i++){
        int j = sqrt(i);
        int flag = 0;
        for(;j>=2;j--){
            if(i%j==0){
                flag = 1;
                break;
            }
        }
        if(!flag)    prime[++p_count] = i;
    }
    // cout<<"Display Q=="<<endl;
    // display(prime);
    // cout<<"Display Q End"<<endl;
    // exit(0);
    int p_size = prime.size();
    int n = number.size();
    vector<int> last(n,0);
    vector<int> temp;
    vector<int> hashTable[p_size];
    
    stack<int> st1, st2;
    for(int i=0; i<n; i++){
        st1.push(number[i]);
    }
    int swtc = 0;
    for(int t=1;t<=q; t++){
        if(!swtc){
            for(int i=st1.size(); !st1.empty(); i--){
                if((st1.top())%prime[t] ==0){
                    hashTable[t].push_back(st1.top());
                    st1.pop();
                }
                else{
                    st2.push(st1.top());
                    st1.pop();
                }
            }
            swtc =1 ;
        }
        else{
            while( !st2.empty()){
                // cout<<"S2.top="<<st2.top()<<",Prime["<<t<<"]="<<prime[t]<<endl;
                if((st2.top()) % prime[t] ==0){
                    hashTable[t].push_back(st2.top());
                    st2.pop();
                }
                else{
                    st1.push(st2.top());
                    st2.pop();
                }
            }
            swtc = 0;
        }
    }
    for(int k = 1; k<=q; k++){
        int l = hashTable[k].size();
        for(int m =l-1; m>=0; m--){
            temp.push_back(hashTable[k][m]);
        }
    }
    if(!st1.empty() && st2.empty()){
        while(!st1.empty()){
            temp.push_back(st1.top());
            st1.pop();
        }
    }
    else if(st1.empty() && !st2.empty()){
        while(!st2.empty()){
            temp.push_back(st2.top());
            st2.pop();
        }
    }
    return temp;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nq_temp;
    getline(cin, nq_temp);

    vector<string> nq = split_string(nq_temp);

    int n = stoi(nq[0]);

    int q = stoi(nq[1]);

    string number_temp_temp;
    getline(cin, number_temp_temp);

    vector<string> number_temp = split_string(number_temp_temp);

    vector<int> number(n);

    for (int number_itr = 0; number_itr < n; number_itr++) {
        int number_item = stoi(number_temp[number_itr]);

        number[number_itr] = number_item;
    }

    vector<int> result = waiter(number, q);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
