#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> answer(200001, 0);
map<int, vector<int>> index;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, k; cin >> n >> k;
        index.clear();
        fill(answer.begin(), answer.end(), 0);        
        
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (index[x].size() < k)
                index[x].push_back(i);
        }

        int m = 0;
        for (auto e : index) m += e.second.size();
        m -= m % k;
        int color = 0;

        for (auto e : index)
            for (auto idx : e.second) {
                answer[idx] = ++color;
                color %= k;
                if (--m == 0) goto _output;
            }

_output:
        for (int i = 0; i < n; ++i)
            cout << answer[i] << " ";
        cout << "\n";
        
    }
       
    return 0;
}