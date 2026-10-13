struct MinCostMaxFlow {
    struct Edge { int to, reverse; ll capacity, cost, flow; };
    vector<vector<Edge>> graph;

    MinCostMaxFlow(int n) : graph(n) {}

    void addEdge(int from, int to, ll capacity, ll cost) {
        graph[from].push_back({to, (int)graph[to].size(), capacity, cost, 0});
        graph[to].push_back(
            {from, (int)graph[from].size() - 1, 0, -cost, 0});
    }

    // Assumes no reachable negative-cost cycle with residual capacity.
    // Returns as much flow as possible up to limit, and its minimum cost.
    pair<ll, ll> minCostFlow(int source, int sink, ll limit = LLONG_MAX) {
        int n = (int)graph.size();
        const ll INF = (1LL << 62);
        vector<ll> potential(n, INF);
        potential[source] = 0;
        for (int iteration = 0; iteration < n - 1; ++iteration) {
            bool changed = false;
            for (int vertex = 0; vertex < n; ++vertex)
                if (potential[vertex] != INF)
                    for (const Edge& edge : graph[vertex])
                        if (edge.capacity > edge.flow
                                && potential[edge.to] >
                                   potential[vertex] + edge.cost) {
                            potential[edge.to] = max(-INF,
                                potential[vertex] + edge.cost);
                            changed = true;
                        }
            if (!changed) break;
        }
        for (ll& value : potential) if (value == INF) value = 0;

        ll totalFlow = 0, totalCost = 0;
        vector<ll> distance(n);
        vector<int> parentVertex(n), parentEdge(n);
        while (totalFlow < limit) {
            fill(distance.begin(), distance.end(), INF);
            distance[source] = 0;
            priority_queue<pair<ll, int>,
                vector<pair<ll, int>>, greater<pair<ll, int>>> queue;
            queue.push({0, source});
            while (!queue.empty()) {
                ll currentDistance = queue.top().first;
                int vertex = queue.top().second;
                queue.pop();
                if (currentDistance != distance[vertex]) continue;
                for (int i = 0; i < (int)graph[vertex].size(); ++i) {
                    Edge& edge = graph[vertex][i];
                    if (edge.flow == edge.capacity) continue;
                    ll candidate = currentDistance + edge.cost
                                 + potential[vertex] - potential[edge.to];
                    if (candidate < distance[edge.to]) {
                        distance[edge.to] = candidate;
                        parentVertex[edge.to] = vertex;
                        parentEdge[edge.to] = i;
                        queue.push({candidate, edge.to});
                    }
                }
            }
            if (distance[sink] == INF) break;
            for (int vertex = 0; vertex < n; ++vertex)
                if (distance[vertex] != INF) potential[vertex] += distance[vertex];
            ll add = limit - totalFlow;
            for (int vertex = sink; vertex != source;
                    vertex = parentVertex[vertex]) {
                int previous = parentVertex[vertex];
                Edge& edge = graph[previous][parentEdge[vertex]];
                add = min(add, edge.capacity - edge.flow);
            }
            for (int vertex = sink; vertex != source;
                    vertex = parentVertex[vertex]) {
                int previous = parentVertex[vertex];
                Edge& edge = graph[previous][parentEdge[vertex]];
                edge.flow += add;
                graph[edge.to][edge.reverse].flow -= add;
                totalCost += add * edge.cost;
            }
            totalFlow += add;
        }
        return {totalFlow, totalCost};
    }
};
