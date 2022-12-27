#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, h, m, answer = 4;
bool ladder[11][31];

bool go(int target) {

    int cur = target;
    int now = 1;

    while (now <= h) {
        if (ladder[cur - 1][now]) --cur;
        else if (ladder[cur][now]) ++cur;
        ++now;
    }

    return (cur == target);
}

void back_track(int depth, int add, int cnt) {
    if (add == cnt) {
        bool result = true;
        for (int i = 1; i <= n && result; ++i) result &= go(i);
        if (result) answer = add;
        return;
    }

    for (int d = depth; d <= h; ++d) {
        for (int cur = 1; cur <= n; ++cur) {
            if (ladder[cur - 1][d] | ladder[cur][d] | ladder[cur + 1][d]) continue;
            ladder[cur][d] = true;
            back_track(d, add, cnt + 1);
            ladder[cur][d] = false;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> h;
    
    memset(ladder, false, sizeof(ladder));
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        ladder[b][a] = true;
    }

    for (int add = 0; add <= 3; ++add) {
        if (answer != 4) break;
        back_track(1, add, 0);
    }

    cout << (answer == 4 ? -1 : answer) << "\n";

    return 0;
}