#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool check(vector<int> &p, int n) {
    for (int i = 0; i < n; ++i) {
        if (p[i] != i % 3) return false;    
    }
    return true;
}

void move(vector<int> &p, vector<int> &s, int n) {
    vector<int> temp(n, 0);
    for (int i = 0; i < n; ++i) {
        temp[s[i]] = p[i];
    }
    p = temp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> p(n);
    vector<int> s(n);

    for (int &e : p) cin >> e;
    for (int &e : s) cin >> e;

    int answer = 0;

    if (check(p, n)) answer = 0;
    while (!check(p, n) && answer <= 1e6) {
        ++answer;
        move(p, s, n);
    }

    if (answer == 1e6 + 1) answer = -1;
    cout << answer << "\n";
    return 0;
}