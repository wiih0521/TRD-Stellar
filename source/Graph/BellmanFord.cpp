struct BFEdge { int from, to; ll weight; };

// INF: unreachable, -INF: reachable from a negative cycle. O(VE).
pair<vector<ll>, vector<int>> bellmanFord(
        int n, const vector<BFEdge>& edges, int source) {
    const ll INF = (1LL << 62);
    vector<ll> distance(n, INF);
    vector<int> parent(n, -1), bad(n);
    distance[source] = 0;
    for (int iteration = 0; iteration < n; ++iteration) {
        bool changed = false;
        for (auto edge : edges) {
            if (distance[edge.from] == INF) continue;
            ll candidate = max(-INF, distance[edge.from] + edge.weight);
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                parent[edge.to] = edge.from;
                changed = true;
                if (iteration == n - 1) bad[edge.to] = true;
            }
        }
        if (!changed) break;
    }
    for (int iteration = 0; iteration < n; ++iteration)
        for (auto edge : edges)
            if (bad[edge.from]) bad[edge.to] = true;
    for (int vertex = 0; vertex < n; ++vertex)
        if (bad[vertex]) distance[vertex] = -INF;
    return {distance, parent};
}
