#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;

    for (int testcase = 1; ; ++testcase) {
        cin >> s; 
        if (s[0] == '-') break;

        int answer = 0;
        stack<char> st;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '{') st.push(s[i]);
            else {
                if (st.empty()) {
                    st.push('}');
                } else {
                    if (st.top() == '{') st.pop();
                    else st.push('}');
                }
            }
        }

        int closeCnt = 0, openCnt = 0;
        while (!st.empty()) {
            if (st.top() == '}') {
                if (closeCnt == 1) {
                    ++answer;
                    closeCnt = 0;
                } else closeCnt = 1;
            } else {
                if (closeCnt == 1) closeCnt = 0;
                else {
                    ++answer;
                    closeCnt = 1;
                }
            }
            st.pop();
        }

        cout << testcase << ". " << answer << "\n";
    }
    return 0;
}