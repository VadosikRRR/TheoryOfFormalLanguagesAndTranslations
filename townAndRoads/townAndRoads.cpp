#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("example_input.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, len;
        fin >> u >> v >> len;
        g[u].push_back({v, len});
        g[v].push_back({u, len});
    }

    int k;
    fin >> k;
    vector<int> capitals(k + 1);
    for (int i = 1; i <= k; ++i) {
        fin >> capitals[i];
    }

    vector<int> owner(n + 1, 0);
    vector<vector<int>> states(k + 1);

    for (int s = 1; s <= k; ++s) {
        int c = capitals[s];
        owner[c] = s;
        states[s].push_back(c);
    }

    int assigned = 0;
    for (int v = 1; v <= n; ++v) {
        if (owner[v] != 0) assigned++;
    }

    while (assigned < n) {
        bool progress = false;

        for (int s = 1; s <= k; ++s) {
            int bestCity = -1;
            int bestDist = INT_MAX;

            for (int city : states[s]) {
                for (const auto &edge : g[city]) {
                    int to = edge.first;
                    int len = edge.second;
                    if (owner[to] != 0) continue;

                    if (len < bestDist || (len == bestDist && to < bestCity)) {
                        bestDist = len;
                        bestCity = to;
                    }
                }
            }

            if (bestCity != -1) {
                owner[bestCity] = s;
                states[s].push_back(bestCity);
                assigned++;
                progress = true;
            }
        }

        if (!progress) {
            break;
        }
    }

    for (int s = 1; s <= k; ++s) {
        sort(states[s].begin(), states[s].end());
        cout << "State " << s << ":";
        for (int city : states[s]) {
            cout << ' ' << city;
        }
        cout << '\n';
    }

    return 0;
}
