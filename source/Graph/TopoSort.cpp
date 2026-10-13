// Returns fewer than n vertices iff the directed graph has a cycle. O(V+E).
vector<int> topologicalSort(const vector<vector<int>>& graph) {
    int n = (int)graph.size();
    vector<int> degree(n), order;
    for (const auto& edges : graph)
        for (int to : edges) ++degree[to];
    for (int vertex = 0; vertex < n; ++vertex)
        if (!degree[vertex]) order.push_back(vertex);
    for (int at = 0; at < (int)order.size(); ++at)
        for (int to : graph[order[at]])
            if (!--degree[to]) order.push_back(to);
    return order;
}
