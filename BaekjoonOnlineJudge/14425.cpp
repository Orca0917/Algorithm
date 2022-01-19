#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    set<string> s;

    int answer = 0;
    while (n--) {
        string str; cin >> str;
        s.insert(str);
    }

    while (m--) {
        string targ; cin >> targ;
        auto it = s.lower_bound(targ);
        if (it == s.end()) continue;
        else if (*it == targ) ++answer;
    }

    cout << answer << "\n";
    return 0;
}