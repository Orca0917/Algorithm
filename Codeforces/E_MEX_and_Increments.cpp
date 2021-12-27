#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> A, C, digitCount;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;

        digitCount.assign(200001, 0);

        for (int i = 0; i < n; ++i) {
            int k; cin >> k; ++digitCount[k];
        }

        ll memo = 0;
        bool prevOK = true;
        stack<int> st;

        for (int MEX = 0; MEX <= n; ++MEX) {
            ll result = 0;
            
            if (MEX > 0 && digitCount[MEX - 1] == 0) {
                if (st.empty()) {
                    prevOK = false;
                } else {
                    int x = st.top(); st.pop();
                    memo += MEX - 1 - x;
                }
            }

            while (MEX > 0 && digitCount[MEX - 1] > 1) {
                digitCount[MEX - 1]--;
                st.push(MEX - 1);
            }

            if (!prevOK) cout << -1 << " ";
            else {
                result = digitCount[MEX] + memo;
                cout << result << " ";
            }

        }
        cout << "\n";
    }
       
    return 0;
}