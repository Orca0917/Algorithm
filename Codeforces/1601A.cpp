#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int bitCount[31];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> arr(n);
        for (auto &e : arr) cin >> e;
        memset(bitCount, 0, sizeof(bitCount));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j <= 30; ++j)
                if (arr[i] & (1 << j))
                    ++bitCount[j];

        vector<int> answer;
        for (int k = n; k >= 1; --k) {
            bool flag = true;
            for (int i = 0; i <= 30 && flag; ++i)
                if (bitCount[i] % k != 0)
                    flag = false;
            if (flag) answer.emplace_back(k);
        }

        sort(answer.begin(), answer.end());

        for (auto ans : answer) cout << ans << " ";
        cout << "\n";
    }

    return 0;

}