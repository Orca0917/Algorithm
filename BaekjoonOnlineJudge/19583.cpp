#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    set<string> s;

    string start, end, real_end;
    cin >> start >> end >> real_end;

    string chat_time, name;

    int answer = 0;

    while (cin >> chat_time >> name) {
        if (chat_time <= start) {
            s.emplace(name);
        }

        else if (end <= chat_time && chat_time <= real_end && !s.empty()) {
            auto it = s.find(name);
            if (it != s.end()) {
                s.erase(it);
                ++answer;
            }
        }
    }

    cout << answer << "\n";
    return 0;
}