// Randomized phase-based Kuhn for a bipartite graph.
// graph[u] contains right-side neighbors of left vertex u.
// Each phase visits every left vertex at most once; shuffling avoids bad orders.
// Returns a maximum matching in rightToLeft. Worst case: O(VE).
int dfsMatching(vector<vector<int>> graph, vector<int>& rightToLeft) {
    int n = (int)graph.size(), m = (int)rightToLeft.size();
    vector<int> leftToRight(n, -1), seen(n), order(n);
    iota(order.begin(), order.end(), 0);
    fill(rightToLeft.begin(), rightToLeft.end(), -1);

    unsigned seed = (unsigned)chrono::steady_clock::now()
        .time_since_epoch().count();
    static mt19937 rng(seed);
    shuffle(order.begin(), order.end(), rng);
    for (auto& edges : graph) shuffle(edges.begin(), edges.end(), rng);

    int matching = 0, timer = 0;
    function<bool(int)> augment = [&](int u) {
        if (seen[u] == timer) return false;
        seen[u] = timer;
        for (int v : graph[u]) {
            assert(0 <= v && v < m);
            if (rightToLeft[v] == -1 || augment(rightToLeft[v])) {
                leftToRight[u] = v;
                rightToLeft[v] = u;
                return true;
            }
        }
        return false;
    };

    bool improved = true;
    while (improved) {
        improved = false;
        ++timer;
        for (int u : order) {
            if (leftToRight[u] == -1 && augment(u)) {
                ++matching;
                improved = true;
            }
        }
    }
    return matching;
}
