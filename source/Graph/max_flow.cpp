/*
Usage: 
 - Dinic(n, s, t): initialize a graph of size n, with s and t being the source and sink nodes, respectively
 - add_edge(u, v, w): add an edge from u to v, with capacity w. 
 - max_flow(): compute maximum flow 
*/
struct Dinic {
    struct Edge { int to, rev; ll cap, flow; };
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic(int n, int source, int sink) : n(n), s(source), t(sink), adj(n), level(n), ptr(n) {}

    void add_edge(int u, int v, ll cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap, 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap - e.flow > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, ll flow) {
        if (u == t || flow == 0) return flow;
        for (; ptr[u] < (int)adj[u].size(); ++ptr[u]) {
            Edge &e = adj[u][ptr[u]];
            if (level[e.to] == level[u] + 1 && e.cap - e.flow > 0) {
                ll pushed = dfs(e.to, min(flow, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    adj[e.to][e.rev].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    void reset_flows() {
        for (auto &u_edges : adj) {
            for (auto &e : u_edges) {
                e.flow = 0; // Reset flow to 0
            }
        }
    }

    ll max_flow() {
        ll flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, LLONG_MAX)) {
                flow += pushed;
            }
        }
        reset_flows();
        return flow;
    }
};