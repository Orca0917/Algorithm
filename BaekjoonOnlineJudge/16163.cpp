#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int range[4000004];

void manacher(vector<char> &s)
{
    int r = 0, p = 0;
    memset(range, 0, sizeof(range));

    for (int i = 0; i < s.size(); ++i)
    {

        if (i > r)
            range[i] = 0;
        else
            range[i] = min(r - i, range[2 * p - i]);

        while (i - range[i] - 1 >= 0 && i + range[i] + 1 < s.size() && s[i - range[i] - 1] == s[i + range[i] + 1])
            ++range[i];

        if (r < i + range[i])
        {
            r = i + range[i];
            p = i;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    vector<char> s_str;
    for (char c : s)
    {
        s_str.push_back('#');
        s_str.push_back(c);
    }
    s_str.push_back('#');

    manacher(s_str);

    ll sum = 0;
    for (int i = 0; i < s_str.size(); ++i)
    {

        // cout << range[i] << " ";
        sum += (range[i] + 1) / 2;
    }

    cout << sum << "\n";
    return 0;
}