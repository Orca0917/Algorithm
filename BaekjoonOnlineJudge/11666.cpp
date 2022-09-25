#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    ++m;
    
    vector<pii> users(n);
    for (pii &user : users) {
        cin >> user.first >> user.second;
        user.second = user.first + user.second - 1;
    }

    sort(users.begin(), users.end());

    multiset<int> ms;
    for (int i = 0; i < n; ++i) {
        int x = users[i].first - m;
        auto it = ms.lower_bound(x);
        
        if (it != ms.end() && *it < users[i].first) ms.erase(it);
        ms.insert(users[i].second);
    }

    cout << n - ms.size() << "\n";
    
    
    return 0;
}