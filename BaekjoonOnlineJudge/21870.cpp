#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll calc_gcd(vector<int> &S, int start, int end) {
    ll result = S[start];
    for (int i = start + 1; i <= end; ++i) {
        result = __gcd(result, 1LL * S[i]);
    }

    return result;
}


ll solve(vector<int> &S, int start, int end) {
    // S의 원소의 개수
    int n = end - start + 1;

    // 만약, S의 원소가 단 한 개라면 그 원소를 선택한다.
    if (n == 1) return S[start];

    // 왼쪽부터 floor(n / 2.0) 또는 오른쪽부터 ceil(n / 2.0) 개 선택
    int left = (int)floor(n / 2.0);
    int right = (int)ceil(n / 2.0);

    ll res1 = calc_gcd(S, start, start + left - 1);    // 왼쪽 선택 결과
    ll res2 = calc_gcd(S, end - right + 1, end);         // 오른쪽 선택 결과

    ll LEFT = res1 + solve(S, start + left, end);      // 왼쪽 선택했을 때
    ll RIGHT = res2 + solve(S, start, end - right);     // 오른쪽 선택했을 때

    return max(LEFT, RIGHT);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> S(n);
    for (int &e : S) cin >> e;

    ll result = solve(S, 0, n - 1);
    cout << result << "\n";
    

    return 0;
}
