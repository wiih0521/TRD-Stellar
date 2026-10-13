// Heavy-light decomposition. processPath emits half-open position intervals.
struct HLD {
    int timer = 0;
    vector<vector<int>> tree;
    vector<int> parent, depth, size, head, position;

    HLD(vector<vector<int>> graph, int root = 0)
        : tree(move(graph)), parent(tree.size(), -1), depth(tree.size()),
          size(tree.size(), 1), head(tree.size()), position(tree.size()) {
        dfsSize(root, -1);
        head[root] = root;
        dfsHld(root, -1);
    }

    void dfsSize(int vertex, int previous) {
        parent[vertex] = previous;
        int heavy = -1;
        for (int to : tree[vertex]) if (to != previous) {
            depth[to] = depth[vertex] + 1;
            dfsSize(to, vertex);
            size[vertex] += size[to];
            if (heavy == -1 || size[to] > size[heavy]) heavy = to;
        }
        if (heavy != -1) {
            auto it = find(tree[vertex].begin(), tree[vertex].end(), heavy);
            swap(tree[vertex][0], *it);
        }
    }

    void dfsHld(int vertex, int previous) {
        position[vertex] = timer++;
        bool firstChild = true;
        for (int to : tree[vertex]) if (to != previous) {
            head[to] = firstChild ? head[vertex] : to;
            firstChild = false;
            dfsHld(to, vertex);
        }
    }

    template<class F>
    void processPath(int a, int b, F operation, bool valuesOnEdges = false) const {
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            operation(position[head[a]], position[a] + 1);
            a = parent[head[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        operation(position[a] + valuesOnEdges, position[b] + 1);
    }

    pair<int, int> subtreeInterval(int vertex, bool valuesOnEdges = false) const {
        return {position[vertex] + valuesOnEdges,
                position[vertex] + size[vertex]};
    }
};
