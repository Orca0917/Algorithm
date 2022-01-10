#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m && n && m) {
        vector<int> H(m + 1, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            stack<int> st; 
            for (int j = 0; j < m + 1; ++j) {
                int x;
                if (j < m) cin >> x;
                else if (j == m) x = 0;

                H[j] = (H[j] + 1) * x;

                while (!st.empty() && H[st.top()] >= H[j]) {
                    int k = st.top(); st.pop();
                    int width = -1;

                    if (st.empty()) width = j;
                    else width = (j - st.top() - 1);

                    result = max(result, H[k] * width);
                }
                st.push(j);
            }
        }
        cout << result << "\n";
    }
    
    return 0;
}