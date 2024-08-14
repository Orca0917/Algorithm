#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
string s;
vector<string> a;

int solve(int index) {
    
    queue<int> pq;
    vector<bool> vis(s.length(), false);

    vis[0] = true;
    pq.push(0);

    while (!pq.empty()) {
        // 문자열 s의 index 번째 위치부터 비교해야 한다.
        int index = pq.front(); pq.pop();

        // 문자열이 완벽히 일치하여, s.length() 위치에 도달하였다.
        if (index == s.length()) return 1;

        // 가능한 모든 문자열을 넣어본다.
        for (string &word : a) {
            int word_len = word.length();
            if (index + word_len > s.length()) continue;  // 문자를 붙였더니 길이를 넘어버림

            // 단어의 길이가 계속 일치하는가?
            bool same = true;
            for (int i = 0; i < word_len && same; ++i) {
                if (s[index + i] != word[i]) same = false;
            }

            // 이미 그 위치에 이전에 간적이 있으면 굳이..
            if (!same || vis[index + word_len]) continue;
            vis[index + word_len] = true;
            pq.push(index + word_len);
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s >> n;
    
    a.resize(n);
    for (string &e: a) cin >> e;

    cout << solve(0);
    
    return 0;
}