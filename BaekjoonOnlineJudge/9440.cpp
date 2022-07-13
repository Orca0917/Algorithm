#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (true) {
        // 숫자의 개수 입력
        int N; cin >> N;
        if (N == 0) break;

        // 숫자의 개수만큼 어떤 수들이 있는지 입력
        vector<int> arr(N);
        for (int &e : arr) cin >> e;

        // 입력받은 숫자들 정렬 (오름차순)
        sort(arr.begin(), arr.end());
        int zero_cnt = lower_bound(arr.begin(), arr.end(), 1) - arr.begin();
        
        vector<int> resort_arr;
        resort_arr.push_back(arr[zero_cnt]);
        resort_arr.push_back(arr[zero_cnt + 1]);
        for (int i = 0; i < zero_cnt; ++i) resort_arr.push_back(0);
        for (int i = zero_cnt + 2; i < N; ++i) resort_arr.push_back(arr[i]);

        int num1 = 0, num2 = 0, start_idx = 0;

        // 숫자의 개수가 홀수라면, 가장 작은수 빼주기
        if (N % 2) {
            num1 += resort_arr[0];
            start_idx = 1;
        }

        // 나머지 하나씩 번갈아가면서 num1, num2 생성
        for (int i = start_idx; i < N; i += 2) {
            num1 = num1 * 10 + resort_arr[i];
            num2 = num2 * 10 + resort_arr[i + 1];
        }

        cout << num1 + num2 << "\n";

    }
    return 0;
}