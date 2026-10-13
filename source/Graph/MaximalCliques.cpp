using CliqueMask = bitset<128>;

template<class F>
void maximalCliqueDfs(const vector<CliqueMask>& adjacency, F& callback,
        CliqueMask candidates, CliqueMask excluded, CliqueMask current) {
    if (!candidates.any()) {
        if (!excluded.any()) callback(current);
        return;
    }
    int pivot = (int)(candidates | excluded)._Find_first();
    CliqueMask branch = candidates & ~adjacency[pivot];
    for (int vertex = 0; vertex < (int)adjacency.size(); ++vertex)
        if (branch[vertex]) {
            current[vertex] = true;
            maximalCliqueDfs(adjacency, callback,
                candidates & adjacency[vertex],
                excluded & adjacency[vertex], current);
            current[vertex] = false;
            candidates[vertex] = false;
            excluded[vertex] = true;
        }
}

// Calls callback once for every maximal clique. n <= 128, O(3^(n/3)).
template<class F>
void enumerateMaximalCliques(const vector<CliqueMask>& adjacency, F callback) {
    assert(adjacency.size() <= 128);
    CliqueMask candidates;
    for (int i = 0; i < (int)adjacency.size(); ++i) candidates[i] = true;
    maximalCliqueDfs(adjacency, callback, candidates, {}, {});
}
