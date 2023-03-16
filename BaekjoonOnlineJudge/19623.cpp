#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Meeting {
    int start_time;
    int end_time;
    int people;
};

int memo[100001];
int num_meets;
vector<Meeting> meeting;


int dp(int idx) {
    if (idx == num_meets) return 0;

    int &ret = memo[idx];
    if (ret != -1) return ret;

    // 참여 안는 경우
    ret = dp(idx + 1);

    // 참여하는 경우
    Meeting meet;
    meet.start_time = meeting[idx].end_time;
    int next_meet = lower_bound(meeting.begin(), meeting.end(), meet, [](const Meeting &meet1, const Meeting &meet2) {
        return meet1.start_time < meet2.start_time;
    }) - meeting.begin();
    ret = max(ret, dp(next_meet) + meeting[idx].people);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> num_meets;
    meeting.resize(num_meets);

    for (int i = 0; i < num_meets; ++i) {
        cin >> meeting[i].start_time >> meeting[i].end_time >> meeting[i].people;
    }

    sort(meeting.begin(), meeting.end(), [](const Meeting &meet1, const Meeting &meet2) -> bool {
        return meet1.start_time < meet2.start_time;
    });


    memset(memo, -1, sizeof(memo));
    cout << dp(0) << "\n";
    
    return 0;
}