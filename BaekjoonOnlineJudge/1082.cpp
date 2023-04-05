#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
vector<int> p(10);
string memo[11][51];

string cmp(string a, string b) {
    if (a.length() > b.length()) return a;
    else if (a.length() < b.length()) return b;

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    return max(a, b);
}

// 현재 돈으로 i~9를 가지고 만들 수 있는 최대의 수
string dp(int index, int money) {
    if (index == n || money <= 0) return "";

    string &ret = memo[index][money];
    if (ret != "*") return ret;

    ret = "";
    for (int i = index; i < n; ++i) {
        if (money - p[i] >= 0)
            ret = cmp(ret, to_string(i) + dp(i, money - p[i]));
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];
    cin >> m;

    for (int i = 0; i < 11; ++i)
        for (int j = 0; j < 51; ++j)
            memo[i][j] = "*";

    string answer = (p[0] <= m ? "0" : "");
    for (int i = 1; i < n; ++i) {
        if (m - p[i] >= 0)
            answer = cmp(answer, to_string(i) + dp(0, m - p[i]));
    }

    sort(answer.rbegin(), answer.rend());
    cout << answer << "\n";
    
    return 0;
}