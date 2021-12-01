// CF

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;

    while (testcase--) {
        int numbers, diff;
        cin >> numbers >> diff;

        vector<int> v(numbers), cop;
        bool isSorted = true;
        int bef = 0;
        for (int i = 0; i < numbers; ++i) {
            cin >> v[i];
            if (bef > v[i]) isSorted = false;
            bef = v[i];
        }
       
        cop = v;
        sort(cop.begin(), cop.end());

        // Sorting이 불가능한 구간
        int start = numbers - diff;
        int end = diff - 1;

        bool flag = false;
        for (int i = start; i <= end && !flag; ++i) {
            if (v[i] != cop[i]) {
                flag = true;
            }
        }

        if (flag) cout << "NO";
        else cout << "YES";

        cout << "\n";
    }

    return 0;

}