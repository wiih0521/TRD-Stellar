struct PushRelabel {
    struct Edge { int to, reverse; ll flow, capacity; };
    vector<vector<Edge>> graph;
    vector<ll> excess;
    vector<Edge*> current;
    vector<vector<int>> active;
    vector<int> height;

    PushRelabel(int n)
        : graph(n), excess(n), current(n), active(2 * n), height(n) {}

    void addEdge(int from, int to, ll capacity, ll reverseCapacity = 0) {
        if (from == to) return;
        graph[from].push_back({to, (int)graph[to].size(), 0, capacity});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0,
                             reverseCapacity});
    }

    void addFlow(Edge& edge, ll amount) {
        Edge& reverse = graph[edge.to][edge.reverse];
        if (!excess[edge.to] && amount)
            active[height[edge.to]].push_back(edge.to);
        edge.flow += amount;
        edge.capacity -= amount;
        excess[edge.to] += amount;
        reverse.flow -= amount;
        reverse.capacity += amount;
        excess[reverse.to] -= amount;
    }

    ll maxFlow(int source, int sink) {
        int n = (int)graph.size();
        height[source] = n;
        excess[sink] = 1;
        vector<int> count(2 * n);
        count[0] = n - 1;
        for (int i = 0; i < n; ++i) current[i] = graph[i].data();
        for (Edge& edge : graph[source]) addFlow(edge, edge.capacity);
        for (int highest = 0;;) {
            while (active[highest].empty())
                if (!highest--) return -excess[source];
            int vertex = active[highest].back();
            active[highest].pop_back();
            while (excess[vertex] > 0) {
                if (current[vertex] == graph[vertex].data() + graph[vertex].size()) {
                    height[vertex] = INT_MAX;
                    for (Edge& edge : graph[vertex])
                        if (edge.capacity && height[vertex] > height[edge.to] + 1)
                            height[vertex] = height[edge.to] + 1,
                            current[vertex] = &edge;
                    ++count[height[vertex]];
                    if (!--count[highest] && highest < n)
                        for (int i = 0; i < n; ++i)
                            if (highest < height[i] && height[i] < n)
                                --count[height[i]], height[i] = n + 1;
                    highest = height[vertex];
                } else if (current[vertex]->capacity
                        && height[vertex] == height[current[vertex]->to] + 1) {
                    addFlow(*current[vertex],
                            min(excess[vertex], current[vertex]->capacity));
                } else {
                    ++current[vertex];
                }
            }
        }
    }

    bool sourceSideOfMinCut(int vertex) const {
        return height[vertex] >= (int)graph.size();
    }
};
