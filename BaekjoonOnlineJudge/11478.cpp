#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    set<string> word_set;

    for (int i = 0; i < s.length(); ++i) {
        string word;
        for (int j = i; j < s.length(); ++j) {
            word += s[j];
            word_set.emplace(word);
        }
    }

    cout << word_set.size() << "\n";
    return 0;
}