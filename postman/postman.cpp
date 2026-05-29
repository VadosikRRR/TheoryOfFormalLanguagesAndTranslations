#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("example_input.txt");
    int n, m;
    fin >> n >> m;

    const int INF = 1000000000;

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<int> degree(n, 0);

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    int sumEdges = 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        int w;
        fin >> u >> v >> w;
        --u;
        --v;

        sumEdges += w;
        degree[u]++;
        degree[v]++;

        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vector<int> odd;
    odd.reserve(n);
    for (int v = 0; v < n; ++v) {
        if (degree[v] % 2 == 1) odd.push_back(v);
    }

    int k = (int)odd.size();
    if (k == 0) {
        cout << sumEdges << '\n';
        return 0;
    }

    int fullMask = (1 << k) - 1;
    vector<int> dp(1 << k, INF);
    dp[0] = 0;

    for (int mask = 0; mask <= fullMask; ++mask) {
        if (dp[mask] == INF) continue;

        int first = -1;
        for (int i = 0; i < k; ++i) {
            if ((mask & (1 << i)) == 0) {
                first = i;
                break;
            }
        }

        if (first == -1) continue;

        for (int j = first + 1; j < k; ++j) {
            if (mask & (1 << j)) continue;

            int newMask = mask | (1 << first) | (1 << j);
            int add = dist[odd[first]][odd[j]];
            dp[newMask] = min(dp[newMask], dp[mask] + add);
        }
    }

    int answer = sumEdges + dp[fullMask];
    cout << answer << '\n';

    return 0;
}
