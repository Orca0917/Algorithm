#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MOD 12345678910

using namespace std;

int N;
stack<ll> st;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;
    
    for (int i = 0; i < N; ++i) {
        char c; cin >> c;

        // 0 : (
        if (c == '0') {
            st.push(-1LL);
        }

        // 1 : )
        else if (c == '1') {
            if (st.top() == -1) {
                st.pop();
                st.push(1LL);
            } else {
                ll temp_score = 0;
                while (!st.empty() && st.top() != -1) {
                    temp_score += st.top();
                    st.pop();
                }
                st.pop();
                st.push((temp_score * 2) % MOD);
            }
        }
    }

    
    ll answer = 0;
    while (!st.empty()) {
        answer += st.top();
        answer %= MOD;
        st.pop();
    }

    cout << answer % MOD << "\n";
    return 0;
}