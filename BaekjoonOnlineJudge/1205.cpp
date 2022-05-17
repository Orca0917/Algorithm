#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
	int songScore;
	int cut;

	cin >> n >> songScore >> cut;

	vector<int> vec(n);

	for (int i = 0; i < n; i++)
	{
		int score;
		cin >> score;
		vec.push_back(score);
	}
		
	sort(vec.rbegin(), vec.rend());

	int bigger = 0;
	int same = 0;

	for (int i = 0; i < n; i++)
	{
		if (vec[i] > songScore)
			bigger++;
		else if (vec[i] == songScore)
			same++;
		else
			break;
	}

	if (bigger + same < cut)
		cout << bigger + 1;
	else
		cout << -1;

    return 0;
}