#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> arr(n);
    
    for (int &e : arr) cin >> e;

    ll answer = 0;
    while (arr.size() > 1) {
        sort(arr.begin(), arr.end());
        int last = arr.size() - 1;

        answer += arr[last - 1];
        int left = arr[last] - arr[last - 1];
        arr.pop_back();
        arr.pop_back();

        if (left) arr.push_back(left);
    }

    if (arr.size()) answer += arr[0];

    cout << (answer > 1440 ? -1 : answer) << "\n";

    return 0;
}