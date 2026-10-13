// Branch-and-bound with greedy coloring. adjacency is symmetric; n <= 200.
struct MaximumClique {
    using Mask = bitset<200>;
    vector<Mask> adjacency;
    vector<int> best, current;

    MaximumClique(vector<Mask> graph) : adjacency(move(graph)) {
        assert(adjacency.size() <= 200);
    }

    void colorSort(const vector<int>& candidates,
            vector<int>& order, vector<int>& bound) {
        vector<Mask> colorClass;
        for (int vertex : candidates) {
            int color = 0;
            while (color < (int)colorClass.size()
                    && (colorClass[color] & adjacency[vertex]).any())
                ++color;
            if (color == (int)colorClass.size()) colorClass.push_back({});
            colorClass[color][vertex] = true;
        }
        for (int color = 0; color < (int)colorClass.size(); ++color)
            for (int vertex : candidates)
                if (colorClass[color][vertex]) {
                    order.push_back(vertex);
                    bound.push_back(color + 1);
                }
    }

    void expand(const vector<int>& candidates) {
        vector<int> order, bound;
        colorSort(candidates, order, bound);
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            if ((int)current.size() + bound[i] <= (int)best.size()) return;
            int vertex = order[i];
            current.push_back(vertex);
            vector<int> next;
            for (int j = 0; j < i; ++j)
                if (adjacency[vertex][order[j]]) next.push_back(order[j]);
            if (next.empty()) {
                if (current.size() > best.size()) best = current;
            } else {
                expand(next);
            }
            current.pop_back();
        }
    }

    vector<int> solve() {
        vector<int> vertices(adjacency.size());
        iota(vertices.begin(), vertices.end(), 0);
        sort(vertices.begin(), vertices.end(), [&](int a, int b) {
            return adjacency[a].count() > adjacency[b].count();
        });
        expand(vertices);
        return best;
    }
};

vector<int> maximumIndependentSet(vector<bitset<200>> adjacency) {
    int n = (int)adjacency.size();
    for (int i = 0; i < n; ++i) {
        adjacency[i].flip();
        adjacency[i][i] = false;
        for (int j = n; j < 200; ++j) adjacency[i][j] = false;
    }
    return MaximumClique(move(adjacency)).solve();
}
