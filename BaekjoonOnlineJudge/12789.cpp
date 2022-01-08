#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> x(n);
    for (int &e: x) cin >> e;

    stack<int> st;
    int target = 1;
    for (int i = 0; i < n; ) {
        if (x[i] == target) {
            ++target;
            i++;
        } else if (!st.empty() && st.top() == target) {
            ++target;
            st.pop();
        } else {
            st.push(x[i]);
            i++;
        }
    }

    while (!st.empty()) {
        if (st.top() == target) {
            st.pop();
            ++target;
        } else break;
    }

    if (st.empty()) cout << "Nice\n";
    else cout << "Sad\n";

    return 0;
}