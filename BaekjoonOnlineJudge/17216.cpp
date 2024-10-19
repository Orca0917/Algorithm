#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;
int memo[1001];

int dp(int index) {
    int &ret = memo[index];
    if (ret != -1) return ret;

    ret = arr[index];
    for (int i = 0; i < index; ++i) {
        if (arr[i] > arr[index]) {  // 감소하는 수열
            ret = max(ret, arr[index] + dp(i));
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(memo, -1, sizeof(memo));

    cin >> n;
    arr.resize(n);

    for (int &e : arr) cin >> e;

    int answer = 0;

    // 각 인덱스에서 끝나는 최대 합 계산
    for (int i = 0; i < n; ++i) {
        answer = max(answer, dp(i));
    }

    cout << answer;

    return 0;
}
