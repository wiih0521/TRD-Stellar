/*
Usage: 
 - Blossom(n): initialize a graph of size n
 - add_edge(u, v): add an edge from u to v
 - max_matching(): compute max matching
*/

struct Blossom {
    int N;
    vector<int> match, par, base, vis;
    vector<vector<int>> adj;
    queue<int> Q;

    Blossom(int n) : N(n), match(n, -1), par(n, -1), base(n), vis(n, -1), adj(n) {
        iota(base.begin(), base.end(), 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int find_lca(int u, int v) {
        vector<bool> visited(N);
        while (1) {
            u = base[u];
            visited[u] = true;
            if (match[u] == -1) break;
            u = par[match[u]];
        }
        while (1) {
            v = base[v];
            if (visited[v]) return v;
            v = par[match[v]];
        }
    }

    void blossom(int u, int v, int lca) {
        while (base[u] != lca) {
            par[u] = v;
            v = match[u];
            if (vis[v] == 1) Q.push(v), vis[v] = 0;
            base[u] = base[v] = lca;
            u = par[v];
        }
    }

    bool bfs(int root) {
        fill(vis.begin(), vis.end(), -1);
        Q = queue<int>();
        Q.push(root), vis[root] = 0;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int v : adj[u]) {
                if (vis[v] == -1) {
                    vis[v] = 1, par[v] = u;
                    if (match[v] == -1) {
                        while (u != -1) {
                            int next_u = match[u];
                            match[u] = v, match[v] = u;
                            v = next_u, u = (v == -1) ? -1 : par[v];
                        }
                        return true;
                    }
                    Q.push(match[v]), vis[match[v]] = 0;
                } else if (vis[v] == 0 && base[u] != base[v]) {
                    int lca = find_lca(u, v);
                    blossom(u, v, lca);
                    blossom(v, u, lca);
                }
            }
        }
        return false;
    }

    int max_matching() {
        int res = 0;
        for (int u = 0; u < N; ++u)
            if (match[u] == -1 && bfs(u))
                ++res;
        return res;
    }
};