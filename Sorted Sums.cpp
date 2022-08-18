#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'sortedSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */
class BIT{
public:
    int size;
    vector<long long> v;
    BIT(int s){
        size = s;
        v.resize(s, 0);
    }
    void update(int i, int delta){
        while(i < size){
            v[i] += delta;
            i += i & (-i);
        }
    }
    long long sum(int i){
        long long s = 0;
        while(i > 0){
            s += v[i];
            i -= i & (-i);
        }
        return s;
    }
};
int sortedSum(vector<int> v,int n) {
    int N = 1e6 + 1, M = 1e9 + 7;
    BIT *pre = new BIT(N), *post = new BIT(N);
    long long fn = v[0], ans = fn, totSum = fn;
    pre->update(v[0], 1);
    post->update(v[0], v[0]);
    for(int i = 1; i < n; i++) {
        int rank = pre->sum(v[i]) + 1;
        long long sumGreaterThanI = totSum - post->sum(v[i]);
        fn = (fn + rank * 1ll * v[i] + sumGreaterThanI) % M;
        ans = (ans + fn) % M;
        pre->update(v[i], 1);
        post->update(v[i], v[i]);
        totSum += v[i];
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a_count_temp;
    getline(cin, a_count_temp);

    int a_count = stoi(ltrim(rtrim(a_count_temp)));

    vector<int> a(a_count);

    for (int i = 0; i < a_count; i++) {
        string a_item_temp;
        getline(cin, a_item_temp);

        int a_item = stoi(ltrim(rtrim(a_item_temp)));

        a[i] = a_item;
    }

    int result = sortedSum(a,a.size());

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}