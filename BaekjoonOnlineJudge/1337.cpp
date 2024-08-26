#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    vector<int> v(n);
    for (int &e : v) cin >> e;

    sort(v.begin(), v.end());

    int answer = 1e9;
    for (int &e : v) {
        int start = e;      // 시작수
        int end = e + 4;    // 연속된다면 끝나는 수

        auto sit = lower_bound(v.begin(), v.end(), start);
        auto eit = lower_bound(v.begin(), v.end(), end);

        // 시작수와 끝 수 사이에 몇개의 숫자가 있나?
        int we_have = distance(sit, eit);

        // end라는 숫자를 가지고 있다면 하나 더해줘야 함! (lower_bound 특성..)
        if (eit != v.end() && *eit == end) ++we_have;
        
        // 계속해서 가장 적은 것으로 업데이트
        answer = min(answer, 5 - we_have);
    }

    cout << answer;
    
    return 0;
}