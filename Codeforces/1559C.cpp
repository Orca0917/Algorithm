#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int testcase;
	cin >> testcase;
	
	while(testcase--) {
		bool isFound = false;
		int city; cin >> city;
		vector<int> v(city + 2);
		for (int i = 1; i <= city; ++i) cin >> v[i];
		
		if (v[1] == 1) {
			cout << city + 1<< " ";
			for (int i = 1; i <= city; ++i) cout << i << " ";
			cout << "\n";
			isFound = true;;
		} else {
			for (int i = 1; i < city; ++i)
				if (v[i] == 0 && v[i + 1] == 1) {
					isFound = true;
					for (int j = 1; j <= i; ++j) cout << j << " ";
					cout << city + 1<< " ";
					for (int j = i + 1; j <= city; ++j) cout << j << " ";
					cout << "\n";
					break;
				}
		}
		
		if (isFound) continue;
		for (int i = 1; i <= city + 1; ++i) cout << i << " ";
		cout << "\n";
	}
	
	return 0;
}