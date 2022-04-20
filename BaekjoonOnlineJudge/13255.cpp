#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;
    double answer = n;

    while (k--) {
        int flip; cin >> flip;
        double temp = 0;
        temp += answer * (1 - (double)flip / n);
        temp += (n - answer) * ((double)flip / n);
        answer = temp;
    }

    cout.precision(15);

    cout << fixed << answer << "\n";
    return 0;
}