#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
vector<int> red, blue;

int testcase;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        arr.resize(n, 0);
        red.clear();
        blue.clear();

        for (int i = 0; i < n; ++i) cin >> arr[i];
        for (int i = 0; i < n; ++i) {
            char c; cin >> c;
            if (c == 'R')
                red.push_back(arr[i]);
            else
                blue.push_back(arr[i]);
        }

        sort(red.rbegin(), red.rend());
        sort(blue.begin(), blue.end());

        bool flag = false;
        for (int i = 0; i < red.size() && !flag; ++i) {
            if (red[i] > n - i) flag = true;
        }

        for (int i = 0; i < blue.size() && !flag; ++i) {
            if (blue[i] < i + 1) flag = true;
        }

        if (flag) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}