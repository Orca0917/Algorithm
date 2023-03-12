#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> v(n);
    for (int &e : v) cin >> e;

    int answer = 2e9;
    for (auto cur = v.begin(); cur != v.end(); ++cur) {
        int e = *cur;
        auto it = lower_bound(v.begin(), v.end(), -e);
        
        if (it == v.end()) it = prev(it);

        if (it != cur && abs(answer) > abs(e + *it)) answer = e + *it;
        if (it != v.begin())
            if (abs(answer) > abs(e + *prev(it)))
                answer = e + *prev(it);
    }   

    cout << answer << "\n";

    return 0;
}