#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int kth(std::vector<int> &a, int k) {
    std::nth_element(a.begin(), a.begin() + k - 1, a.end());
    return a[k - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<int> arr = {1, 1, 2, 2, 2, 3, 3, 3};
    cout << kth(arr, 5);

    return 0;
}