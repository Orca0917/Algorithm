#include <iostream>
#include <vector>
#include <algorithm>

#define INF 9000000000000000000
#define ll long long
using namespace std;

ll n, m, defense = 0;
vector<ll> hero;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n;
	hero.resize(n);
	for (auto &e: hero) {
		cin >> e;
		defense += e;
	}
	sort(hero.begin(), hero.end());

	cin >> m;
	for (int i = 0; i < m; ++i) {
		ll attack, health; cin >> health >> attack;
		int idx = lower_bound(hero.begin(), hero.end(), health) - hero.begin();
		int idx2 = upper_bound(hero.begin(), hero.end(), health) - hero.begin();
		
		ll answer = INF, answer1 = INF, answer2 = INF;

		if (idx < n && hero[idx] == health) {
			// 현재 영웅의 공격력과 용의 체력이 일치. (최적의 선택)
			answer = attack - (defense - hero[idx]);
			if (answer < 0) answer = 0;
		}

		// 코인을 사용하여 영웅의 공격력을 올려서 용을 물리치는 경우
		if (idx - 1 >= 0) {
			// 영웅을 강화하는데 사용한 코인
			ll coin1 = health - hero[idx - 1];
			if (coin1 < 0) coin1 = 0;
			// 나머지 영웅들이 수호하는데 사용한 코인
			ll coin2 = attack - (defense - hero[idx - 1]);
			if (coin2 < 0) coin2 = 0;

			answer1 = coin1 + coin2;
		}

		// 용보다 더 강한 영웅을 내세워서 용을 물리치는 경우
		if (idx2 < n) {
			// 영웅을 강화할 필요 없음.
			ll coin1 = 0;
			ll coin2 = attack - (defense - hero[idx2]);
			if (coin2 < 0) coin2 = 0;
			answer2 = coin1 + coin2;
		}
		answer = min({answer, answer1, answer2});

		cout << answer << "\n";
	}
	return 0;
}