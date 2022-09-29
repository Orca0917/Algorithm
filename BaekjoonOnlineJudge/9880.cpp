#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<pii> v(n);
    for (pii &e : v) cin >> e.first >> e.second;

    sort(v.begin(), v.end(), [](const pii &a, const pii &b) {
        return a.second < b.second;
    });

    int answer = 0;
    multiset<int> ms;
    for (int i = 0; i < n; ++i) {
        auto it = ms.lower_bound(-v[i].first);
        
        if (it == ms.end()) {
            if (ms.size() < 2) {
                ms.insert(-v[i].second);
                ++answer;
            }
        } 
        
        else {
            ms.erase(it);
            ms.insert(-v[i].second);
            ++answer;   
        }
    }

    cout << answer << "\n";
    
    return 0;
}