#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 10001
using namespace std;

int p1[MAX], p2[MAX];
int p1_cnt = 0, p2_cnt = 0;
int arr[MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        if (p1[arr[i]]++ == 0) ++p1_cnt;
    }

    int left = 0, right = -1;
    int answer = 1e9;
    int color;

    while (left < n && right < n) {
        if (p2_cnt < k) {
            color = arr[++right];
            if (--p1[color] == 0) p1_cnt--;
            if (p2[color]++ == 0) p2_cnt++;
        } 
        
        else {
            if (p2_cnt == k && p1_cnt == k) answer = min(answer, right - left + 1);

            color = arr[left++];
            if (p1[color]++ == 0) p1_cnt++;
            if (--p2[color] == 0) p2_cnt--;
        }
    }

    cout << (answer == 1e9 ? 0 : answer) << "\n";

    return 0;
}