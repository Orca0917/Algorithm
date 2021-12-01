#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // make accumulative sum (2^0, 2^1, 2^2, ... 2^50)
    // answer++; if: 2^height <= h
    // then, sum value to sum[h_max] - sum[height]
    // answer += ceil(sum_value / processor)


    int testcase; cin >> testcase;
    while (testcase--) {
        int h, p; cin >> h >> p;
        ll answer = 0;
        int i = 0;
        for (i = 0; i < h; ++i) {
            if ((1LL << i) <= p) ++answer;
            else break;
        }

        ll remain = (1LL << h) - 1 - ((1LL << i) - 1);
        answer +=  remain / p;
        if (remain % p) answer++;

        cout << answer << "\n";
    }
    return 0;

}