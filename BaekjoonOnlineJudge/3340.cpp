#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<bool> vis(10000001, false);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int c, n; cin >> c >> n;
    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> answer;

    for (int i = n - 1; i >= 0; --i) {
        int targ = v[i];
        if (vis[targ]) continue;
        else {
            answer.push_back(targ);
            vis[targ] = true;
        }
    }

    cout << answer.size() << "\n";
    for (int i = answer.size() - 1; i >= 0; --i) cout << answer[i] << " ";
    return 0;
}