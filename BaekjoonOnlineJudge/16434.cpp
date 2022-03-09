#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct HERO {
    ll max_hp; // 용사의 최대 생명력입니다. 이 값은 1이상이어야 하며 던전에 들어간 이후로 변하지 않습니다.
    ll cur_hp; // 현재 용사의 생명력입니다. 던전에 들어가기 전 이 값은 용사의 최대 생명력 HMaxHP와 같습니다. 이 값은 HMaxHP보다 커질 수 없습니다.
    ll atk; // 용사의 공격력입니다.
};

struct ROOM {
    int option;
    ll attk;
    ll health;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    HERO hero;
    int n, atk;
    cin >> n >> atk;

    vector<ROOM> room(n);
    for (int i = 0; i < n; ++i) {
        cin >> room[i].option >> room[i].attk >> room[i].health;
    }


    auto do_fight = [&](const ll health_val) -> bool {

        bool ret = true;
        
        hero.atk = atk;
        hero.max_hp = health_val;
        hero.cur_hp = health_val;

        for (int i = 0; i < n; ++i) {
            if (room[i].option == 1) {

                // 용사가 이기려면 몇 번 공격을 해야하나
                ll attk_cnt = room[i].health / hero.atk;
                if (room[i].health % hero.atk) attk_cnt += 1;
                
                // 용사가 그만큼 공격하고도 살아있으면 ok
                hero.cur_hp -= room[i].attk * (attk_cnt - 1);
                if (hero.cur_hp <= 0) {
                    return false;
                } 
            }

            // 포션
            else {
                hero.atk += room[i].attk;
                hero.cur_hp += room[i].health;
                hero.cur_hp = min(hero.cur_hp, hero.max_hp);
            }
        }

        return ret;
    };

    ll lo = 1, hi = 1e19;
    ll answer = 1;

    while (lo <= hi) {
        ll mid = (lo + hi) / 2LL;
        if (do_fight(mid)) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}