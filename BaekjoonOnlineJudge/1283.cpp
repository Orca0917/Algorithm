#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int convert(char c) {
    if ('A' <= c && c <= 'Z') c = c - 'A' + 'a';
    return c - 'a';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    string buf; getline(cin, buf);
    vector<string> answer[31];
    bool hasKey[31];
    memset(hasKey, false, sizeof(hasKey));

    for (int i = 0; i < n; ++i) {
        string sen;
        getline(cin, sen);

        istringstream ss(sen);
        string word;

        vector<string> v;
        while (getline(ss, word, ' ')) {
            v.push_back(word);
        }

        bool success = false;
        for (string &s: v) {
            if (!hasKey[convert(s[0])]) {
                success = true;
                hasKey[convert(s[0])] = success;
                s = "[" + s.substr(0, 1) + "]" + s.substr(1);
                break;
            }
        }

        if (success == false) {
            for (string &s : v) {
                for (int j = 1; j < s.length(); ++j) {
                    if (!hasKey[convert(s[j])]) {
                        success = true;
                        hasKey[convert(s[j])] = success;
                        s = s.substr(0, j) + "[" + s.substr(j, 1) + "]" + s.substr(j + 1);
                        break;
                    }
                }
                if (success) break;
            }
        }

        for (string s : v) {
            answer[i].push_back(s);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (string s : answer[i])
            cout << s << " ";
        cout << "\n";
    }
    return 0;
}