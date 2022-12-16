#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<pair<double, int>> users;

bool has_selected[101];
double score, _sum = 0;
int person;
int n, m, k, cnt = 0;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> person >> score;
            users.push_back({score, person});
        }
    }

    sort(users.begin(), users.end(), [](const pair<double, int> &a, const pair<double, int> &b) {
        return a.first > b.first;
    });
    
    
    memset(has_selected, false, sizeof(has_selected));
    
    for (auto user : users) {
        if (has_selected[user.second]) continue;
        _sum += user.first;
        has_selected[user.second] = true;
        if (++cnt == k) break;
    }

    printf("%.1lf\n", _sum);

    return 0;
}
