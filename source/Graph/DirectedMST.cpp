struct DMSTEdge { int from, to; ll weight; };

struct RollbackDSU {
    vector<int> data;
    vector<pair<int, int>> history;
    RollbackDSU(int n) : data(n, -1) {}
    int find(int x) { return data[x] < 0 ? x : find(data[x]); }
    int time() const { return (int)history.size(); }
    void rollback(int time) {
        while ((int)history.size() > time) {
            auto change = history.back();
            history.pop_back();
            data[change.first] = change.second;
        }
    }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (data[a] > data[b]) swap(a, b);
        history.push_back({a, data[a]});
        history.push_back({b, data[b]});
        data[a] += data[b];
        data[b] = a;
        return true;
    }
};

struct DMSTHeap {
    DMSTEdge edge;
    DMSTHeap *left = nullptr, *right = nullptr;
    ll lazy = 0;
    void push() {
        edge.weight += lazy;
        if (left) left->lazy += lazy;
        if (right) right->lazy += lazy;
        lazy = 0;
    }
};

DMSTHeap* mergeDMST(DMSTHeap* a, DMSTHeap* b) {
    if (!a || !b) return a ? a : b;
    a->push(); b->push();
    if (a->edge.weight > b->edge.weight) swap(a, b);
    a->right = mergeDMST(b, a->right);
    swap(a->left, a->right);
    return a;
}

void popDMST(DMSTHeap*& heap) {
    heap->push();
    heap = mergeDMST(heap->left, heap->right);
}

// Minimum rooted arborescence. Returns {-1,{}} if some node is unreachable.
// parent[root] is -1. O(E log V).
pair<ll, vector<int>> directedMST(
        int n, int root, const vector<DMSTEdge>& edges) {
    RollbackDSU dsu(n);
    vector<DMSTHeap*> heap(n);
    for (auto edge : edges)
        if (edge.from != edge.to)
            heap[edge.to] = mergeDMST(heap[edge.to],
                new DMSTHeap{edge, nullptr, nullptr, 0});
    ll answer = 0;
    vector<int> seen(n, -1), path(n), parent(n, -1);
    seen[root] = root;
    vector<DMSTEdge> queue(n), incoming(n, {-1, -1, 0});
    struct Cycle {
        int representative, rollbackTime;
        vector<DMSTEdge> edges;
    };
    deque<Cycle> cycles;
    for (int start = 0; start < n; ++start) {
        int vertex = start, queueSize = 0;
        while (seen[vertex] < 0) {
            while (heap[vertex]
                    && dsu.find(heap[vertex]->edge.from) == vertex)
                popDMST(heap[vertex]);
            if (!heap[vertex]) return {-1, {}};
            heap[vertex]->push();
            DMSTEdge edge = heap[vertex]->edge;
            heap[vertex]->lazy -= edge.weight;
            popDMST(heap[vertex]);
            queue[queueSize] = edge;
            path[queueSize++] = vertex;
            seen[vertex] = start;
            answer += edge.weight;
            vertex = dsu.find(edge.from);
            if (seen[vertex] == start) {
                DMSTHeap* cycleHeap = nullptr;
                int end = queueSize, rollbackTime = dsu.time(), member;
                do {
                    member = path[--queueSize];
                    cycleHeap = mergeDMST(cycleHeap, heap[member]);
                } while (dsu.join(vertex, member));
                vertex = dsu.find(vertex);
                heap[vertex] = cycleHeap;
                seen[vertex] = -1;
                cycles.push_front({vertex, rollbackTime,
                    vector<DMSTEdge>(queue.begin() + queueSize,
                                     queue.begin() + end)});
            }
        }
        for (int i = 0; i < queueSize; ++i)
            incoming[dsu.find(queue[i].to)] = queue[i];
    }
    for (const Cycle& cycle : cycles) {
        dsu.rollback(cycle.rollbackTime);
        DMSTEdge entering = incoming[cycle.representative];
        for (auto edge : cycle.edges)
            incoming[dsu.find(edge.to)] = edge;
        incoming[dsu.find(entering.to)] = entering;
    }
    for (int vertex = 0; vertex < n; ++vertex)
        if (vertex != root) parent[vertex] = incoming[vertex].from;
    return {answer, parent};
}
