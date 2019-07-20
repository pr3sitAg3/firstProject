#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the waiter function below.
 */
void display(vector<int> v){
     int n = v.size();
     for(int i=0; i<n; i++)
        cout<<v[i]<<",";
    cout<<"End of Display"<<endl;
}

vector<int> waiter(vector<int> number, int q) {
    vector<int> prime;
    for(int i=2; i<1201; i++){
        int j = sqrt(i);
        int flag = 0;
        for(;j>=2;j--){
            if(i%j==0){
                flag = 1;
                break;
            }
        }
        if(!flag)    prime.push_back(i);
    }
    int p_size = prime.size();
    int n = number.size();
    vector<int> last(n,0);
    vector<int> temp;
    vector<int> hashTable[p_size];

    for(int t=0;t<q; t++){
        cout<<"Prime t="<<prime[t]<<endl;
        for(int i=0; i<n; i++){
                if(number[i]%prime[t] == 0 && last[i]==0){
                    last[i] = 1;
                    temp.push_back(number[i]);
                    break;
                }
        }
        if(last[i]){

        }
    }
    cout<<"**********************"<<endl;
    display(last);
    display(number);
    cout<<"**********************"<<endl;
    int i=0;
    while(i<n){
        if(!last[i]){
            temp.push_back(number[i]);
        }
        i++;
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
