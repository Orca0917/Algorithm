#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    while (true) {
        getline(cin, s);
        if (s == "#") break;

        string tags;
        bool hasOpen = false;
        bool illegal = false;
        stack<string> st;
        for (int i = 0; i < s.length() && !illegal; ++i) {
            if (s[i] == '<') {
                hasOpen = true;
            } else if (s[i] == '>') {
                if (tags.back() == '/') {
                    // cout << tags << "는 열고닫기를 다 했음\n";
                    goto INIT;
                } else {
                    stringstream ss(tags);
                    string token;
                    bool hasFirst = false;
                    while(getline(ss, token, ' ') && !hasFirst) {
                        tags = token;
                        hasFirst = true;
                    }

                    if (tags.front() == '/') {
                    
                        // 닫는 태그이기 때문에 스택에서 뽑아야 한다.
                        if (!st.empty() && st.top() == tags.substr(1)) {
                            // cout << tags << " 는 이전 태그와 매칭이 되었음\n";
                            st.pop();
                        } else {
                            // cout << tags << " 는 맞지 않는 태그임\n";
                            illegal = true;
                            break;
                        }
                    } else {
                        // cout << tags << " 여는 태그를 삽입한다.\n";
                        st.push(tags);
                    }
                }

            INIT:
                tags = "";
                hasOpen = false;
            } else if (hasOpen) {
                tags += s[i];
            }
        }

        if (illegal || !st.empty()) cout << "illegal\n";
        else cout << "legal\n";

    }
    return 0;
}