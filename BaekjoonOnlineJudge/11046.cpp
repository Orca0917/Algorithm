#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int range[2000002];

void manacher(vector<int> &s) {
    int r = 0, p = 0;
    memset(range, 0, sizeof(range));

    for (int i = 0; i < s.size(); ++i) {

        if (i > r) range[i] = 0;
        else range[i] = min(r - i, range[2 * p - i]);

        while (i - range[i] - 1 >= 0 && i + range[i] + 1 < s.size() && s[i - range[i] - 1] == s[i + range[i] + 1]) ++range[i];

        if (r < i + range[i]) {
            r = i + range[i];
            p = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; ++i) {
        nums.push_back(0);
        int k; cin >> k;
        nums.push_back(k);
    } nums.push_back(0);

    manacher(nums);


    int query; cin >> query;
    while (query--) {
        int start, end; cin >> start >> end;
        int quest = end - start;

        start = 2 * start - 1;
        end = 2 * end - 1;
        int mid = (start + end) / 2;
        // 0 1 0 2 0 1 0 3 0 1 0 2 0 1 0
        int len = range[mid];

        if (quest <= len) cout << "1\n";
        else cout << "0\n";
    }

    return 0;
}