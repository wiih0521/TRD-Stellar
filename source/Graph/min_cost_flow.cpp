/*
Usage: 
 - MCMF(n, s, t): initialize a graph of size n, with s and t being the source and sink nodes, respectively
 - add_edge(u, v, c, w): add an edge from u to v, with capacity c and cost w. 
 - minCostFlow(): compute {flow, min_cost} 
*/

struct MCMF {
    struct Edge { int v, cap, cost, rev; };
    int N, s, t;
    vector<vector<Edge>> adj;
    vector<int> dist, parent, parentEdge, inQueue;

    MCMF(int n, int s, int t) : N(n), s(s), t(t), adj(n), dist(n), parent(n), parentEdge(n), inQueue(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        adj[u].push_back({v, cap, cost, (int)adj[v].size()});
        adj[v].push_back({u, 0, -cost, (int)adj[u].size() - 1});
    }

    bool spfa(int s, int t) {
        fill(dist.begin(), dist.end(), INT_MAX);
        queue<int> q;
        dist[s] = 0; q.push(s); inQueue[s] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop(); inQueue[u] = 0;
            for (int i = 0; i < adj[u].size(); ++i) {
                Edge &e = adj[u][i];
                if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    parent[e.v] = u; parentEdge[e.v] = i;
                    if (!inQueue[e.v]) q.push(e.v), inQueue[e.v] = 1;
                }
            }
        }
        return dist[t] != INT_MAX;
    }

    pair<int, int> minCostFlow(int k) {
        int flow = 0, cost = 0;
        while (flow < k && spfa(s, t)) {
            int augFlow = k - flow;
            for (int u = t; u != s; u = parent[u])
                augFlow = min(augFlow, adj[parent[u]][parentEdge[u]].cap);

            for (int u = t; u != s; u = parent[u]) {
                Edge &e = adj[parent[u]][parentEdge[u]];
                e.cap -= augFlow;
                adj[u][e.rev].cap += augFlow;
                cost += augFlow * e.cost;
            }

            flow += augFlow;
        }
        return flow == k ? make_pair(flow, cost) : make_pair(-1, -1);
    }
};