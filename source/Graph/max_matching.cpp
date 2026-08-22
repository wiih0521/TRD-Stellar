/*
Usage: 
 - Matching(n, s, t): initialize a graph of size n
 - add_edge(u, v): add an edge from u to v
 - max_matching(): return maximum matching 
*/

struct Matching {
    int n; vector<vector<int>> adj; vector<int> pairU, pairV, dist, color;
    Matching(int n) : n(n), adj(n + 1), pairU(n + 1), pairV(n + 1), dist(n + 1), color(n + 1, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; ++u)
            if (!pairU[u] && color[u] == 0) dist[u] = 0, q.push(u);
            else dist[u] = INT_MAX;
        dist[0] = INT_MAX;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) 
                if (dist[pairV[v]] == INT_MAX)
                    dist[pairV[v]] = dist[u] + 1, q.push(pairV[v]);
        }
        return dist[0] != INT_MAX;
    }

    bool dfs(int u) {
        if (!u) return true;
        for (int v : adj[u]) 
            if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))
                return pairV[v] = u, pairU[u] = v, true;
        dist[u] = INT_MAX;
        return false;
    }

    vector<pair<int, int>> max_matching() {
        function<void(int)> color_graph = [&](int u) {
            for (int v : adj[u]) if (color[v] == -1) color[v] = 1 - color[u], color_graph(v);
        };
        for (int u = 1; u <= n; ++u) if (color[u] == -1) color[u] = 0, color_graph(u);
        while (bfs()) for (int u = 1; u <= n; ++u) if (!pairU[u] && color[u] == 0) dfs(u);
        vector<pair<int, int>> res;
        for (int u = 1; u <= n; ++u) if (pairU[u]) res.emplace_back(u, pairU[u]);
        return res;
    }
};