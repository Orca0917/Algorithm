#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<bool> isPrime(201, true);
void eratos() {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= 200; ++i) {
        if (isPrime[i] == false) continue;
        for (int j = 2; j * i <= 200; ++j)
            isPrime[i * j] = false;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    eratos();

    vector<int> a;
    for (int i = 2; i < 200; ++i)
        if (isPrime[i]) {
            a.push_back(i);
        }
    
    vector<int> v;
    for (int i = 0; i < a.size() - 1; ++i) {
        v.push_back(a[i] * a[i + 1]);
    }

    int k; cin >> k;
    cout << *upper_bound(v.begin(), v.end(), k) << "\n";

    return 0;
}