#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    stack<int> st;
    while (true) {
        getline(cin, s);

        if (s == "고무오리 디버깅 끝") break;

        if (s == "문제") {
            st.push(1);
        }
        else if (s == "고무오리") {
            if (st.empty()) {
                st.push(1);
                st.push(1);
            } else {
                st.pop();
            }
        }
    }

    if (st.empty()) cout << "고무오리야 사랑해\n";
    else cout << "힝구\n";
    return 0;
}