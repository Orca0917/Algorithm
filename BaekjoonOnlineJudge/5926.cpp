#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
set<int> s;
map<int, int> cows;
vector<pii> v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    v.resize(n);

    for (pii &e : v) {
        cin >> e.first >> e.second;
        s.insert(e.second);
    }

    sort(v.begin(), v.end());
    
    int left = 0, right = -1;
    int answer = 2e9;
    int cnts = 0, target = (int)s.size();

    while (left < n && right < n) {
        if (cnts == target) {
            answer = min(answer, v[right].first - v[left].first);
            if (--cows[v[left].second] == 0) --cnts;
            ++left;
        } else {
            ++right;
            if (cows[v[right].second]++ == 0) ++cnts;
        }
    }

    cout << answer << "\n";
    return 0;
}