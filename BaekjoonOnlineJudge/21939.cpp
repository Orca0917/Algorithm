#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int p2rank[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(p2rank, -1, sizeof(p2rank));
    int n; cin >> n;
    
    auto cmp = [](const pii &a, const pii &b) -> bool {
        if (a.second == b.second) return a.first > b.first;
        return a.second > b.second;
    };

    // 어렵고, 문제 번호 높은것이 가장 앞으로 오게끔 만든다.
    set<pii, decltype(cmp)> s(cmp);

    for (int i = 0; i < n; ++i) {
        int num, rank; cin >> num >> rank;
        p2rank[num] = rank;
        s.emplace(num, rank);
    }

    int m; cin >> m;
    while (m--) {
        string option; cin >> option;
        if (option == "add") {
            int num, rank; cin >> num >> rank;
            s.emplace(num, rank);
            p2rank[num] = rank;
        } else if (option == "recommend") {
            int opt; cin >> opt;
            auto it = s.begin();
            if (opt == 1) {
                it = s.begin();
            } else if (opt == -1) {
                it = s.end();
                --it;
            }
            cout << (*it).first << "\n";
        } else if (option == "solved") {
            int num; cin >> num;
            s.erase({num, p2rank[num]});
            p2rank[num] = -1;
        }
    }
    return 0;
}