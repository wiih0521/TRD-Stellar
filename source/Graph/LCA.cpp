struct LCA {
    int timer = 0;
    vector<int> parent, depth, tin, tout;
    vector<vector<int>> jump;

    LCA(const vector<vector<int>>& tree, int root = 0)
        : parent(tree.size(), root), depth(tree.size()),
          tin(tree.size()), tout(tree.size()) {
        int n = (int)tree.size();
        vector<int> iterator(n), stack = {root};
        parent[root] = root;
        while (!stack.empty()) {
            int vertex = stack.back();
            if (!iterator[vertex]) tin[vertex] = timer++;
            if (iterator[vertex] == (int)tree[vertex].size()) {
                tout[vertex] = timer;
                stack.pop_back();
                continue;
            }
            int to = tree[vertex][iterator[vertex]++];
            if (to == parent[vertex]) continue;
            parent[to] = vertex;
            depth[to] = depth[vertex] + 1;
            stack.push_back(to);
        }
        jump = buildJumpTable(parent);
    }

    bool ancestor(int a, int b) const {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }

    int lca(int a, int b) const {
        if (ancestor(a, b)) return a;
        if (ancestor(b, a)) return b;
        for (int level = (int)jump.size() - 1; level >= 0; --level)
            if (!ancestor(jump[level][a], b)) a = jump[level][a];
        return parent[a];
    }

    int distance(int a, int b) const {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};
