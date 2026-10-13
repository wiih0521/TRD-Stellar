using GomoryHuEdge = array<ll, 3>; // {u,v,capacity}

// Requires PushRelabel. Undirected non-negative capacities. O(V) max-flows.
vector<GomoryHuEdge> gomoryHu(int n, const vector<GomoryHuEdge>& edges) {
    vector<GomoryHuEdge> tree;
    vector<int> parent(n);
    for (int vertex = 1; vertex < n; ++vertex) {
        PushRelabel flow(n);
        for (auto edge : edges)
            flow.addEdge((int)edge[0], (int)edge[1], edge[2], edge[2]);
        ll cut = flow.maxFlow(vertex, parent[vertex]);
        tree.push_back({vertex, parent[vertex], cut});
        for (int next = vertex + 1; next < n; ++next)
            if (parent[next] == parent[vertex]
                    && flow.sourceSideOfMinCut(next))
                parent[next] = vertex;
    }
    return tree;
}
