struct FlowWithDemand {
    struct BoundedEdge { int from, to; ll lower, upper; };
    int n, source, sink;
    vector<BoundedEdge> edges;

    FlowWithDemand(int n, int source, int sink)
        : n(n), source(source), sink(sink) {}

    void addEdge(int from, int to, ll lower, ll upper) {
        assert(0 <= lower && lower <= upper);
        edges.push_back({from, to, lower, upper});
    }

    // Whether a feasible s-t flow exists with at most backCapacity total flow.
    // Use LLONG_MAX/4 for an unrestricted feasible flow/circulation.
    bool feasible(ll backCapacity = LLONG_MAX / 4) const {
        int superSource = n, superSink = n + 1;
        Dinic flow(n + 2);
        vector<ll> balance(n);
        for (auto edge : edges) {
            flow.addEdge(edge.from, edge.to, edge.upper - edge.lower);
            balance[edge.from] -= edge.lower;
            balance[edge.to] += edge.lower;
        }
        flow.addEdge(sink, source, backCapacity);
        ll required = 0;
        for (int vertex = 0; vertex < n; ++vertex) {
            if (balance[vertex] > 0) {
                flow.addEdge(superSource, vertex, balance[vertex]);
                required += balance[vertex];
            } else if (balance[vertex] < 0) {
                flow.addEdge(vertex, superSink, -balance[vertex]);
            }
        }
        return flow.maxFlow(superSource, superSink) == required;
    }
};
