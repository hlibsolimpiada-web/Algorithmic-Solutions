#include <bits/stdc++.h>
using namespace std;

static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    struct Edge { int u, v; };
    vector<Edge> edges(M);
    vector<vector<pair<int,int>>> adj(N);

    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v;
        edges[i].u--; edges[i].v--;
        adj[edges[i].u].push_back({edges[i].v, i});
        adj[edges[i].v].push_back({edges[i].u, i});
    }

    vector<bool> visited(N, false);
    vector<int> parent(N, -1);       
    vector<int> par_edge(N, -1);     
    vector<bool> is_tree_edge(M, false);
    vector<int> order;               
    order.reserve(N);

    {
        stack<pair<int,int>> stk;
        stk.push({0, 0});
        visited[0] = true;

        while (!stk.empty()) {
            auto& [u, idx] = stk.top();
            if (idx == (int)adj[u].size()) {
                order.push_back(u); // post-order
                stk.pop();
                continue;
            }
            auto [v, eidx] = adj[u][idx++];
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                par_edge[v] = eidx;
                is_tree_edge[eidx] = true;
                stk.push({v, 0});
            }
        }
    }

    vector<uint64_t> edge_hash(M, 0);

    for (int i = 0; i < M; i++) {
        if (!is_tree_edge[i]) {
            edge_hash[i] = rng();
            while (edge_hash[i] == 0) edge_hash[i] = rng();
        }
    }

    vector<uint64_t> val(N, 0);

    for (int i = 0; i < M; i++) {
        if (!is_tree_edge[i]) {
            val[edges[i].u] ^= edge_hash[i];
            val[edges[i].v] ^= edge_hash[i];
        }
    }

    for (int v : order) {
        if (parent[v] != -1) {
            edge_hash[par_edge[v]] = val[v];
            val[parent[v]] ^= val[v];
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int C;
        cin >> C;
        vector<uint64_t> h(C);
        for (int i = 0; i < C; i++) {
            int eidx;
            cin >> eidx;
            eidx--; 
            h[i] = edge_hash[eidx];
        }

        bool disconnected = false;

        int total = (1 << C);
        for (int mask = 1; mask < total; mask++) {
            uint64_t xor_sum = 0;
            for (int bit = 0; bit < C; bit++) {
                if (mask & (1 << bit)) {
                    xor_sum ^= h[bit];
                }
            }
            if (xor_sum == 0) {
                disconnected = true;
                break;
            }
        }

        cout << (disconnected ? "Disconnected" : "Connected") << '\n';
    }

    return 0;
}
