#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, d, k, c;
    cin >> n >> d >> k >> c;

    vector<int> v(n), cnt(d + 1, 0);

    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i) v.push_back(v[i]);

    int answer = 0, cur = 0;

    // 맨 처음 k 개의 음식
    for (int i = 0; i < k; ++i) ++cnt[v[i]];
    ++cnt[c]; // 서비스 음식

    for (int i = 1; i <= d; ++i) if (cnt[i]) ++cur;
    answer = cur;
    
    for (int i = 1; i < n; ++i) {
        // 이전 초밥 삭제
        cnt[v[i - 1]]--;
        if (cnt[v[i - 1]] == 0) --cur;

        // 새로운 초밥 추가
        if (cnt[v[i + k - 1]] == 0) ++cur;
        cnt[v[i + k - 1]]++;

        answer = max(answer, cur);
    }

    cout << answer << "\n";

    return 0;
}