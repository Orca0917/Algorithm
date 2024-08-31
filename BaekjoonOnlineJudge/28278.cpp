#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    stack<int> st;

    while (n--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            st.push(x);
        }
        else if (op == 2 || op == 5) {
            if (st.empty()) cout << "-1\n";
            else {
                cout << st.top() << "\n";
                if (op == 2) st.pop();
            }
        }
        else if (op == 3) {
            cout << (int)st.size() << "\n";
        }
        else if (op == 4) {
            cout << (int)st.empty() << "\n";
        }
    }
    
    return 0;
}