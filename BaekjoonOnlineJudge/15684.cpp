#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, h, m, answer = 4;
bool ladder[11][31];

bool go(int index) {

    int id = index;
    int now = 1;

    while (now <= h) {
        if (ladder[id - 1][now]) --id;
        else if (ladder[id][now]) ++id;
        ++now;
    }

    return (id == index);
}

void back_track(int depth, int stick, int cnt) {
    if (stick == cnt) {
        bool result = true;
        for (int i = 1; i <= n && result; ++i) result &= go(i);
        if (result) answer = stick;
        return;
    }

    for (int d = depth; d <= h; ++d) {
        for (int index = 1; index <= n; ++index) {
            if (ladder[index - 1][d] | ladder[index][d] | ladder[index + 1][d]) continue;
            ladder[index][d] = true;
            back_track(d, stick, cnt + 1);
            ladder[index][d] = false;
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

    for (int i = 0; i <= 3; ++i) {
        if (answer != 4) break;
        back_track(1, i, 0);
    }

    cout << (answer == 4 ? -1 : answer) << "\n";

    return 0;
}