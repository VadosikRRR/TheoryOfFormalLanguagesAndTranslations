#include <bits/stdc++.h>
using namespace std;

struct Rule {
    char lhs;
    string rhs; // empty string means epsilon
};

static bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

static int rightmostNonTerminalPos(const string &s) {
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        if (isNonTerminal(s[i])) return i;
    }
    return -1;
}

static bool isTerminalString(const string &s) {
    for (char c : s) {
        if (isNonTerminal(c)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("example_input.txt");

    int m;
    fin >> m;

    vector<Rule> rules(m);
    for (int i = 0; i < m; ++i) {
        string lhs, rhs;
        fin >> lhs >> rhs;
        rules[i].lhs = lhs[0];
        rules[i].rhs = (rhs == "eps" ? "" : rhs);
    }

    string alpha;
    int k, maxSteps, maxFormLen;
    fin >> alpha;
    fin >> k;
    fin >> maxSteps >> maxFormLen;

    vector<vector<Rule>> byLhs(26);
    for (const Rule &r : rules) {
        if (isNonTerminal(r.lhs)) {
            byLhs[r.lhs - 'A'].push_back(r);
        }
    }

    struct State {
        string form;
        int steps;
        int lastRuleWasEps; // 1 if last applied rule was epsilon, 0 otherwise, -1 for start
    };

    queue<State> q;
    q.push({alpha, 0, -1});

    // We keep visited by (form, steps) to avoid repeated exploration loops on the same layer.
    set<pair<string, int>> visited;
    visited.insert({alpha, 0});

    set<string> eff;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.steps > maxSteps) continue;

        if (isTerminalString(cur.form)) {
            if (cur.steps > 0 && cur.lastRuleWasEps == 0) {
                string out = cur.form;
                if ((int)out.size() > k) out = out.substr(0, k);
                eff.insert(out);
            }
            continue;
        }

        if (cur.steps == maxSteps) continue;

        int pos = rightmostNonTerminalPos(cur.form);
        if (pos == -1) continue;

        char nt = cur.form[pos];
        const vector<Rule> &cand = byLhs[nt - 'A'];

        for (const Rule &r : cand) {
            string next = cur.form.substr(0, pos) + r.rhs + cur.form.substr(pos + 1);
            if ((int)next.size() > maxFormLen) continue;

            int nextSteps = cur.steps + 1;
            pair<string, int> key = {next, nextSteps};
            if (visited.insert(key).second) {
                q.push({next, nextSteps, r.rhs.empty() ? 1 : 0});
            }
        }
    }

    cout << "EFF_" << k << "(" << alpha << "):" << '\n';
    if (eff.empty()) {
        cout << "<empty>" << '\n';
    } else {
        for (const string &s : eff) {
            cout << s << '\n';
        }
    }

    return 0;
}
