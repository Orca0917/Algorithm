#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 250'001
using namespace std;

int N;
int C;
int arr[MAX];
ll ff[MAX], bb[MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> C;
    for (int i = 1; i <= N; ++i) cin >> arr[i];

    // ff[i] = 1 번째부터 i번째까지 모두 같은 색으로 만들기 위해 눌러야 하는 횟수 (i - 1 까지 색이 맞춰줬다고 가정)
    ff[1] = 0;
    for (int i = 2; i <= N; ++i) {
        ll need = arr[i] - arr[i - 1];
        ff[i] = ff[i - 1] + (need < 0 ? need + C : need);
    }

    // bb[i] = N 번째부터 i번째까지 모두 같은 색으로 만들기 위해 눌러야 하는 횟수 (i + 1 까지 색이 맞춰줬다고 가정)
    bb[N] = 0;
    for (int i = N - 1; i >= 1; --i) {
        ll need = arr[i] - arr[i + 1];
        bb[i] = bb[i + 1] + (need < 0 ? need + C : need);
    }

    // {index, count}
    pair<int, ll> answer = {-1, -1};

    for (int index = 1; index <= N; ++index) {
        ll cnt = max(ff[N] - ff[index], bb[1] - bb[index]);
        if (answer.second == -1 || answer.second > cnt) answer = {index, cnt};
    }

    cout << answer.first << "\n" << answer.second << "\n";
    
    return 0;
}