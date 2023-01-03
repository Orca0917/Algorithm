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

    sort(v.begin(), v.end());

    int answer = 0;
    vector<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.back() > v[i].second) {
            if (st.back()) ++answer;
            st.pop_back();
        }
        if (!st.empty() && st.back() == v[i].second) continue;
        st.push_back(v[i].second);
    }
    while (!st.empty()) {
        if (st.back()) ++answer;
        st.pop_back();
    }

    cout << answer << "\n";
    
    return 0;
}