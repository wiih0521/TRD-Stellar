// Residual capacities are modified. O(VE^2).
template<class T>
T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
    assert(source != sink);
    int n = (int)graph.size();
    T flow = 0;
    vector<int> parent(n), queue(n);
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        int head = 0, tail = 1;
        queue[0] = source;
        while (head < tail && parent[sink] == -1) {
            int vertex = queue[head++];
            for (auto edge : graph[vertex])
                if (edge.second > 0 && parent[edge.first] == -1) {
                    parent[edge.first] = vertex;
                    queue[tail++] = edge.first;
                }
        }
        if (parent[sink] == -1) return flow;
        T add = numeric_limits<T>::max();
        for (int vertex = sink; vertex != source; vertex = parent[vertex])
            add = min(add, graph[parent[vertex]][vertex]);
        flow += add;
        for (int vertex = sink; vertex != source; vertex = parent[vertex]) {
            int previous = parent[vertex];
            if ((graph[previous][vertex] -= add) == 0)
                graph[previous].erase(vertex);
            graph[vertex][previous] += add;
        }
    }
}
