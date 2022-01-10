#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        vector<ll> H(n);
        for (ll &h : H) cin >> h;
        H.push_back(0);

        ll result = 0;
        stack<ll> st;

        for (int i = 0; i < (int)H.size(); ++i) {
            while (!st.empty() && H[st.top()] >= H[i]) {
                ll j = st.top(); st.pop();
                ll width = -1;

                if (st.empty()) width = i;
                else width = i - st.top() - 1;

                result = max(result, H[j] * width);
            }
            st.push(i);
        }
        cout << result << "\n";
    }
    
    return 0;
}