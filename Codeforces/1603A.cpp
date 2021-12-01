#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> arr(n + 1);
        bool result = true;
        for (int i = 1; i <= n; ++i) cin >> arr[i];
        for (int i = 1; i <= n; ++i) {
            bool flag = false;
            for (int j = 2; j <= i + 1 && !flag; ++j)
                if (arr[i] % j) flag = true;
            result &= flag;
        }

        if (result) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}