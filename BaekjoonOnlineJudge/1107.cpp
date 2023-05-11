#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	bool can_press[10];
    memset(can_press, true, sizeof(can_press));

	int target; cin >> target;
	int broken; cin >> broken;

	for (int i = 0; i < broken; i++) {
		int k; cin >> k;
		can_press[k] = false;
	}

    // 1. 숫자누르고 +누르는 경우
	int current = target;
	int answer = 1234567890;
	while (current >= 0) {
		string n = to_string(current);
		bool all_avaiable = true;
        for (char c : n) {
            if (!can_press[c - '0']) all_avaiable = false;
            if (!all_avaiable) break;
        }

		if (all_avaiable) { // 모든버튼 누르기 가능
			answer = min(answer, (int)n.length() + target - current); // 숫자 수 + (+)버튼 누르는 횟수
			break;
		}

		current--;
	}


    // 2. 숫자누르고 -누르는 경우
	current = target;
	while (current <= 1000000) {
		string n = to_string(current);
		bool all_avaiable = true;
		for (char c : n) {
            if (!can_press[c - '0']) all_avaiable = false;
            if (!all_avaiable) break;
        }

		if (all_avaiable) { // 모든버튼 누르기 가능
			answer = min(answer, (int)n.length() + current - target); // 숫자 수 + (-)버튼 누르는 횟수
			break;
		}

		current++;
	}

    // 3. 100번에서 + 또는 -로만 이동하는 경우
	answer = min(answer, abs(100 - target));

	cout << answer << "\n";

	return 0;
}