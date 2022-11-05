#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<string> student_num;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	
	int length = 1;
	int result;

	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		string input; cin >> input;
		reverse(input.begin(), input.end());
		student_num.push_back(input);
	}

	while (1) {
		set <string> s;
		for (int i = 0; i < N; i++)
			s.insert(student_num[i].substr(0, length));
		if (s.size() == N) break;
		else ++length;
	}

	result = length;
	cout << result;
    
    return 0;
}