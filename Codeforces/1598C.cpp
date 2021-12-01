#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

#define ld long double
#define ll long long

using namespace std;

int n;
vector<int> arr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        arr.clear();
        cin >> n;

        arr.resize(n);
        for (int &e : arr) cin >> e;

        ll sum = accumulate(arr.begin(), arr.end(), 0LL);
        sum *= 2;

        if (sum % n) {
            cout << "0\n";
            continue;
        }

        ll avg = sum / n, answer = 0;
        map<int, int> m;
        for (auto e : arr) {
            if (m.count(avg - e) == 1)
                answer += m[avg - e];
            m[e]++;
        }
        cout << answer << "\n";
    }
    return 0;
}