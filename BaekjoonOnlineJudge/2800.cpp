#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

set<string> answer;
vector<pii> parenthesis;

void addAnswer(string s) {
    string result;
    for (int i = 0; i < s.length(); ++i)
        if (s[i] != '#') result += s[i];
    answer.insert(result);
}

void bruteForce(string s, int index) {
    if (index == parenthesis.size()) {
        addAnswer(s);
        return;
    }

    bruteForce(s, index + 1);
    s[parenthesis[index].first] = s[parenthesis[index].second] = '#';
    bruteForce(s, index + 1); 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;

    stack<int> st;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(' || s[i] == ')') {
            if (s[i] == '(') st.push(i);
            else {
                parenthesis.push_back({st.top(), i});
                st.pop();
            }
        } 
    }

    bruteForce(s, 0);
    
    auto it = answer.begin();
    ++it;
    for (it; it != answer.end(); ++it) cout << *it << "\n";

    return 0;
}