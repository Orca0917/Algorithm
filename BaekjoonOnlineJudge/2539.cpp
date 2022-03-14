#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> mM(1000001, 0);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, color_paper, mis_color;
    cin >> n >> m >> color_paper >> mis_color;

    int lim = 0;
    for (int i = 0; i < mis_color; ++i) {
        int x, y; cin >> x >> y;
        mM[y] = max(mM[y], x);
        lim = max(lim, x);
    }

    auto is_available = [&](const int mid) -> bool {
        int paper_cnt = 0;

        assert (lim > mid);

        for (int i = 0; i <= m; ++i) {
            if (mM[i] > 0) {
                i += mid - 1;
                paper_cnt++;
            }
        }

        return paper_cnt <= color_paper;
    };

    int lo = lim, hi = 1e8, answer = lim;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_available(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}