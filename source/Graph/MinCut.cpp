// After max-flow, this returns vertices reachable from source through
// positive residual-capacity edges. Requires Dinic from Max Flow.
vector<int> minCutSide(const Dinic& flow, int source) {
    vector<int> seen(flow.graph.size()), stack = {source}, result;
    seen[source] = true;
    while (!stack.empty()) {
        int vertex = stack.back();
        stack.pop_back();
        result.push_back(vertex);
        for (const auto& edge : flow.graph[vertex])
            if (edge.capacity > 0 && !seen[edge.to]) {
                seen[edge.to] = true;
                stack.push_back(edge.to);
            }
    }
    return result;
}
