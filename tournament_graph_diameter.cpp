#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin >> n) {
        if (n < 3) {
            cout << -1 << "\n";
            continue;
        }

        if (n == 4) {
            cout << -1 << "\n";
            continue;
        }

        vector<vector<int>> adj(n, vector<int>(n, 0));

        int m = (n % 2 == 1) ? n : n - 1;
        int half = (m - 1) / 2;

        for (int i = 0; i < m; i++) {
            for (int k = 1; k <= half; k++) {
                int j = (i + k) % m;
                adj[i][j] = 1;
            }
        }

        if (n % 2 == 0) {
            for (int i = 0; i < m; i++) {
                if (i % 2 == 0) {
                    adj[n - 1][i] = 1;
                } else {
                    adj[i][n - 1] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0) cout << " ";
                cout << adj[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}