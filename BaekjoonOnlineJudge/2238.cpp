#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<string> who[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int u, n; cin >> u >> n;
    for (int i = 0; i < n; ++i) {
        string name; cin >> name;
        int cost; cin >> cost;

        who[cost].push_back(name);
    }

    int min_len = 1e9;
    for (int i = 1; i <= u; ++i) {
        if (who[i].size() > 0)
            min_len = min(min_len, (int)who[i].size());
    }

    for (int i = 1; i <= u; ++i) {
        if (min_len == (int)who[i].size()) {
            cout << who[i][0] << " " << i << "\n";
            break;
        }
    }
    
    return 0;
}