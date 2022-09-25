#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    vector<int> v(n + 2, 1e9);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    ll answer = 0;
    int target = n;

    while (target > 1) {
        vector<int> temp;

        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == target) answer += min(abs(temp.back() - v[i]), abs(v[i] - v[i + 1]));
            else temp.push_back(v[i]);
        }

        v.clear();
        v.assign(temp.begin(), temp.end());

        --target;
    }

    cout << answer << "\n";

    return 0;
}