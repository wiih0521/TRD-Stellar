// Stoer-Wagner for an undirected weighted adjacency matrix. O(V^3).
// Returns {cut weight, one side of the cut}.
pair<ll, vector<int>> globalMinCut(vector<vector<ll>> matrix) {
    int n = (int)matrix.size();
    if (!n) return {0, {}};
    pair<ll, vector<int>> best = {LLONG_MAX, {}};
    vector<vector<int>> groups(n);
    for (int i = 0; i < n; ++i) groups[i] = {i};
    vector<int> alive(n, true);
    for (int phase = 1; phase < n; ++phase) {
        vector<ll> weight(n);
        vector<int> used(n);
        int previous = -1, selected = -1;
        for (int iteration = 0; iteration < n - phase + 1; ++iteration) {
            selected = -1;
            for (int vertex = 0; vertex < n; ++vertex)
                if (alive[vertex] && !used[vertex]
                        && (selected == -1 || weight[vertex] > weight[selected]))
                    selected = vertex;
            if (iteration == n - phase) {
                if (weight[selected] < best.first)
                    best = {weight[selected], groups[selected]};
                if (previous == -1) break;
                for (int vertex = 0; vertex < n; ++vertex) {
                    matrix[previous][vertex] += matrix[selected][vertex];
                    matrix[vertex][previous] = matrix[previous][vertex];
                }
                auto& destination = groups[previous];
                destination.insert(destination.end(),
                    groups[selected].begin(), groups[selected].end());
                alive[selected] = false;
            } else {
                used[selected] = true;
                for (int vertex = 0; vertex < n; ++vertex)
                    if (alive[vertex] && !used[vertex])
                        weight[vertex] += matrix[selected][vertex];
                previous = selected;
            }
        }
    }
    return best;
}
