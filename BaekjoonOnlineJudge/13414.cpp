#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    map<string, int> mm;
    
    int n, m; cin >> n >> m;
    int prior = 1;

    while (m--) {
        string num; cin >> num;
        if (mm.find(num) == mm.end()) mm.emplace(num, prior++);
        else mm[num] = prior++;
    }

    vector<pair<string, int>> v(mm.begin(), mm.end());

    sort(v.begin(), v.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });

    while(n-- && !v.empty()) {
        cout << v.back().first << "\n";
        v.pop_back();
    }
    return 0;
}