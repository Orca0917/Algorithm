#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<string> words[51];
int memo[51];
string sentence;
int len_sentence;

bool check_same(string a, string b) {
    if (a.length() != b.length()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}


int calc_diff(string a, string b) {
    int diff = 0;
    for (int i = 0; i < a.length(); ++i)
        if (a[i] != b[i]) ++diff;
    return diff;
}


int dp(int start) {
    if (start == len_sentence) return 0;

    int &ret = memo[start];
    if (ret != -1) return ret;

    ret = 1e9;
    string made = "";
    for (int i = start; i < sentence.length(); ++i) {
        made += sentence[i];
        int min_diff = 1e9;
        for (string word : words[(int)made.length()]) {
            if (check_same(made, word)) {
                int diff = calc_diff(made, word);
                min_diff = min(min_diff, diff);
            }
        }

        ret = min(ret, dp(i + 1) + min_diff);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> sentence; len_sentence = (int)sentence.length();
    int num_word; cin >> num_word;
    for (int i = 0; i < num_word; ++i) {
        string word; cin >> word;
        words[(int)word.length()].push_back(word);
    }

    memset(memo, -1, sizeof(memo));
    int ret = dp(0);
    cout << (ret == 1e9 ? -1 : ret) << "\n";

    
    return 0;
}