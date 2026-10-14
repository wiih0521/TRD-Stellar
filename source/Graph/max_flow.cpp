struct Dinic {
    struct Edge {
        int to, reverse;
        ll capacity, original;
        ll flow() const { return original - capacity; }
    };
    vector<vector<Edge>> graph;
    vector<int> level, nextEdge;

    Dinic(int n) : graph(n), level(n), nextEdge(n) {}

    void addEdge(int from, int to, ll capacity, ll reverseCapacity = 0) {
        graph[from].push_back(
            {to, (int)graph[to].size(), capacity, capacity});
        graph[to].push_back(
            {from, (int)graph[from].size() - 1,
             reverseCapacity, reverseCapacity});
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> queue;
        level[source] = 0;
        queue.push(source);
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            for (const Edge& edge : graph[vertex])
                if (edge.capacity > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[vertex] + 1;
                    queue.push(edge.to);
                }
        }
        return level[sink] != -1;
    }

    ll dfs(int vertex, int sink, ll pushed) {
        if (vertex == sink || !pushed) return pushed;
        for (int& i = nextEdge[vertex]; i < (int)graph[vertex].size(); ++i) {
            Edge& edge = graph[vertex][i];
            if (edge.capacity > 0 && level[edge.to] == level[vertex] + 1) {
                ll amount = dfs(edge.to, sink, min(pushed, edge.capacity));
                if (amount) {
                    edge.capacity -= amount;
                    graph[edge.to][edge.reverse].capacity += amount;
                    return amount;
                }
            }
        }
        return 0;
    }

    ll maxFlow(int source, int sink, ll limit = LLONG_MAX) {
        ll flow = 0;
        while (flow < limit && bfs(source, sink)) {
            fill(nextEdge.begin(), nextEdge.end(), 0);
            while (flow < limit) {
                ll pushed = dfs(source, sink, limit - flow);
                if (!pushed) break;
                flow += pushed;
            }
        }
        return flow;
    }

    void reset() {
        for (auto& edges : graph)
            for (Edge& edge : edges) edge.capacity = edge.original;
    }

    // S-side of min cut: vertices reachable in residual graph after maxFlow()
    bool inCut(int u) const { return level[u] != -1; }
};
