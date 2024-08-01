#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 참가 팀 수
    int n; cin >> n;

    // 전체 인원의 연령 입력
    vector<int> arr(3 * n);
    for (int &e : arr) cin >> e;
    
    // 오름차순 정렬
    sort(arr.begin(), arr.end());

    // 중앙 N 개의 값중 최대와 최소의 차이를 출력
    cout << arr[2 * n - 1] - arr[n] << "\n";
    
    return 0;
}