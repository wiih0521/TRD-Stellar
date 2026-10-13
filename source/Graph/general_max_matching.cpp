// Edmonds' blossom algorithm for an undirected graph. O(n^3).
struct Blossom {
    int n;
    vector<vector<int>> graph;
    vector<int> match, parent, base, queue;
    vector<bool> used, inBlossom;

    Blossom(int n) : n(n), graph(n), match(n, -1), parent(n),
        base(n), queue(n), used(n), inBlossom(n) {}

    void addEdge(int a, int b) {
        assert(a != b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int lca(int a, int b) {
        vector<bool> seen(n);
        while (true) {
            a = base[a];
            seen[a] = true;
            if (match[a] == -1) break;
            a = parent[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = parent[match[b]];
        }
    }

    void markPath(int vertex, int root, int child) {
        while (base[vertex] != root) {
            inBlossom[base[vertex]] = inBlossom[base[match[vertex]]] = true;
            parent[vertex] = child;
            child = match[vertex];
            vertex = parent[match[vertex]];
        }
    }

    int findPath(int root) {
        fill(used.begin(), used.end(), false);
        fill(parent.begin(), parent.end(), -1);
        iota(base.begin(), base.end(), 0);
        int head = 0, tail = 0;
        queue[tail++] = root;
        used[root] = true;
        while (head < tail) {
            int vertex = queue[head++];
            for (int to : graph[vertex]) {
                if (base[vertex] == base[to] || match[vertex] == to) continue;
                if (to == root || (match[to] != -1
                        && parent[match[to]] != -1)) {
                    int rootBase = lca(vertex, to);
                    fill(inBlossom.begin(), inBlossom.end(), false);
                    markPath(vertex, rootBase, to);
                    markPath(to, rootBase, vertex);
                    for (int i = 0; i < n; ++i)
                        if (inBlossom[base[i]]) {
                            base[i] = rootBase;
                            if (!used[i]) used[i] = true, queue[tail++] = i;
                        }
                } else if (parent[to] == -1) {
                    parent[to] = vertex;
                    if (match[to] == -1) return to;
                    to = match[to];
                    used[to] = true;
                    queue[tail++] = to;
                }
            }
        }
        return -1;
    }

    int maxMatching() {
        int result = 0;
        for (int vertex = 0; vertex < n; ++vertex) if (match[vertex] == -1) {
            int endpoint = findPath(vertex);
            if (endpoint == -1) continue;
            ++result;
            while (endpoint != -1) {
                int previous = parent[endpoint];
                int next = previous == -1 ? -1 : match[previous];
                if (previous != -1)
                    match[endpoint] = previous, match[previous] = endpoint;
                endpoint = next;
            }
        }
        return result;
    }
};
