#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string sentence;
    vector<string> lines[1001];
    int lineIdx = 0;

    while (getline(cin, sentence)) {
        istringstream ss(sentence);
        string token;

        while (getline(ss, token, ' ')) {
            if (token.size() > 0)
                lines[lineIdx].push_back(token);
        }

        ++lineIdx;
    }

    vector<int> maxLen(1000, 0);
    for (int i = 0; i < lineIdx; ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            maxLen[j] = max(maxLen[j], (int)lines[i][j].length());
        }
    }

    for (int i = 0; i < lineIdx; ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            int addBlank = maxLen[j] - (int)lines[i][j].length() + 1;
            if (lines[i][j].length() > 0)
                cout << lines[i][j];
            while (addBlank-- > 0 && j != lines[i].size() - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}