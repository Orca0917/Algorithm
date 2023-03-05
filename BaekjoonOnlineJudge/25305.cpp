#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k; 
    vector<int> arr(n);
    for (int &e : arr) cin >> e;

    sort(arr.rbegin(), arr.rend());
    cout << arr[k - 1] << "\n";
    
    return 0;
}