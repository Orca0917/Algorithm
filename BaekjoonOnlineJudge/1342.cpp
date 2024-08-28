#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

bool is_lucky(string &s) {
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == s[i - 1]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    sort(s.begin(), s.end());

    // 가능한 모든 순열 생성 => 10! 별로 안큼
    int answer = 0;
    do {
        if (is_lucky(s)) ++answer;
    } while (next_permutation(s.begin(), s.end()));

    cout << answer;
    
    return 0;
}