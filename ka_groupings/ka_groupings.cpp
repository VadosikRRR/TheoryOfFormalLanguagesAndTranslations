#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
    int l;
    int r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("example_input.txt");

    int n, m, T;
    fin >> n >> m >> T;

    vector<Edge> edges(m);
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        fin >> edges[i].u >> edges[i].v >> edges[i].l >> edges[i].r;
    }

    const int STEP = 10;

    for (int t = 0; t < T; t += STEP) {
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }

        for (int i = 0; i < m; ++i) {
            // Связь активна на такте, если [t, t+STEP) пересекается с [l, r).
            if (max(t, edges[i].l) < min(t + STEP, edges[i].r)) {
                int u = edges[i].u;
                int v = edges[i].v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        vector<int> used(n + 1, 0);
        vector<vector<int>> groups;

        for (int start = 1; start <= n; ++start) {
            if (used[start]) continue;

            vector<int> comp;
            queue<int> q;
            q.push(start);
            used[start] = 1;

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                comp.push_back(v);

                for (int to : adj[v]) {
                    if (!used[to]) {
                        used[to] = 1;
                        q.push(to);
                    }
                }
            }

            sort(comp.begin(), comp.end());
            groups.push_back(comp);
        }

        sort(groups.begin(), groups.end());

        cout << "Tick [" << t << ", " << min(t + STEP, T) << ")" << '\n';
        for (int i = 0; i < (int)groups.size(); ++i) {
            cout << "Group " << (i + 1) << ":";
            for (int sat : groups[i]) {
                cout << ' ' << sat;
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
