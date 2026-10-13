// Adjacency entries are {destination, global edge id}; both directions of an
// undirected edge share an id. Empty means no trail from source. O(V+E).
vector<int> eulerWalk(const vector<vector<pair<int, int>>>& graph,
        int edgeCount, int source = 0) {
    int n = (int)graph.size();
    vector<int> balance(n), iterator(n), used(edgeCount), result;
    vector<int> stack = {source};
    ++balance[source];
    while (!stack.empty()) {
        int vertex = stack.back();
        int& index = iterator[vertex];
        while (index < (int)graph[vertex].size()
                && used[graph[vertex][index].second]) ++index;
        if (index == (int)graph[vertex].size()) {
            result.push_back(vertex);
            stack.pop_back();
        } else {
            int to = graph[vertex][index].first;
            int edge = graph[vertex][index++].second;
            if (!used[edge]) {
                --balance[vertex];
                ++balance[to];
                used[edge] = true;
                stack.push_back(to);
            }
        }
    }
    for (int value : balance)
        if (value < 0) return {};
    if ((int)result.size() != edgeCount + 1) return {};
    reverse(result.begin(), result.end());
    return result;
}
