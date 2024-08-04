#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Art {
    ll size;
    ll price;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    // n개의 미술품 정보 입력받기
    vector<Art> arts(n);
    for (Art &art : arts) cin >> art.size >> art.price;

    // 크기를 기준으로 정렬
    sort(arts.begin(), arts.end(), [](Art &a, Art &b) -> bool {
        return a.size < b.size;
    });

    // 가격에 대한 누적합을 계산
    vector<ll> psum(n, 0);
    psum[0] = arts[0].price;
    for (int i = 1; i < n; ++i) psum[i] = psum[i - 1] + arts[i].price;

    ll answer = 0;
    ll min_art = arts[0].size;
    for (int i = 0; i < n; ++i) {
        ll max_art = arts[i].size;
        ll current = psum[i] - (max_art - min_art);
        answer = max(answer, current);

        // min 값을 새롭게 업데이트 하는 경우 (=새로운 구간 탐색)
        if (i < n) min_art = max(min_art, arts[i + 1].size - psum[i]);
    }

    cout << answer << "\n";
    
    return 0;
}