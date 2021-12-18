#include <bits/stdc++.h>
using namespace std;

//// init values /////
int n, m;
char board[11][11];
int memo[11][(1 << 11)];
/////////////////////////

int dp(int row, int prevSeats) {
    // �¼��� ���� ���ٿ� �����Ͽ� ���̻� Ȯ���� ���� ����.
    if (row == n) return 0;

    int &ret = memo[row][prevSeats];
    if (ret != -1) return ret;

    ret = 0;
    for (int seats = 0; seats < (1 << m); ++seats) {
        bool canCheat = false; // ���� �¼� �������� ������ �������� �Ǵ��Ѵ�.

        // ���� ��ġ�� �Ұ����� ���: ������ ������ ��� + �¼��� �ļյ� ���
        // 1. ���� ��, �쿡 �ɴ� ���
        // 2. �밢���ڸ��� �ɴ� ���
        // 3. �ڸ��� �ļյ� ���

        // ���� ���ڸ��� ����� �ɴ� ��츦 �����Ѵ�.
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j); // ���� �ڸ��� ����� �ִ���
            bool opt2 = (j > 0) && (seats & (1 << (j - 1))); // ���� ���� �ڸ��� ����� �մ���
            if (opt1 && opt2) {
                // cout << "���ڸ��� ����� �־ ���� ����\n";
                canCheat = true;
            }
        }

        // �밢�� �ڸ��� ����� �ɴ� ��츦 �����Ѵ�.
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j); // ���� �ڸ��� ����� �ִ���
            bool opt2 = (j > 0) && (prevSeats & (1 << (j - 1))); // �밢�� ���ʿ� ����� �ִ���
            bool opt3 = (j < m - 1) && (prevSeats & (1 << (j + 1))); // �밢�� �����ʿ� ����� �ִ���
            if (opt1 && (opt2 || opt3)) {
                // cout << "�밢���� ����� �־ ���� ����\n";
                canCheat = true;
            }
        }

        // ����: ���� �ڸ��� �ļյ� ���
        for (int j = 0; j < m && !canCheat; ++j) {
            bool opt1 = seats & (1 << j);
            bool opt2 = (board[row][j] == 'x');
            if (opt1 && opt2) {
                // cout << "�ڸ��� �ļյǾ ���� ����\n";
                canCheat = true;
            }
        }

        if (canCheat) continue;

        int studentCount = 0; // ���� row�ٿ� �� ���� ���� �� �ִ��� Ȯ���Ѵ�.
        for (int i = 0; i < m; ++i) if (seats & (1 << i)) studentCount++;

        ret = max(ret, dp(row + 1, seats) + studentCount);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        memset(memo, -1, sizeof(memo));

        cin >> n >> m;
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> board[i][j];

        cout << dp(0, 0) << "\n";
    }

    return 0;
}