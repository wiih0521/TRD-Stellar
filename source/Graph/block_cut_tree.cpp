// Vertex-biconnected components and their block-cut forest. O(V+E).
struct BlockCutTree {
    int n, timer = 0;
    vector<vector<pair<int, int>>> graph;
    vector<int> tin, low, edgeStack, articulation, position;
    vector<pair<int, int>> edges;
    vector<vector<int>> blocks, tree;

    BlockCutTree(int n) : n(n), graph(n), tin(n, -1), low(n),
                          articulation(n), position(n, -1) {}

    void addEdge(int a, int b) {
        int id = (int)edges.size();
        edges.push_back({a, b});
        graph[a].push_back({b, id});
        graph[b].push_back({a, id});
    }

    void dfs(int vertex, int parentEdge) {
        tin[vertex] = low[vertex] = timer++;
        int children = 0;
        for (auto item : graph[vertex]) {
            int to = item.first, edge = item.second;
            if (edge == parentEdge) continue;
            if (tin[to] == -1) {
                edgeStack.push_back(edge);
                ++children;
                dfs(to, edge);
                low[vertex] = min(low[vertex], low[to]);
                if (low[to] >= tin[vertex]) {
                    if (parentEdge != -1 || children > 1)
                        articulation[vertex] = true;
                    vector<int> block;
                    while (true) {
                        int id = edgeStack.back();
                        edgeStack.pop_back();
                        block.push_back(edges[id].first);
                        block.push_back(edges[id].second);
                        if (id == edge) break;
                    }
                    sort(block.begin(), block.end());
                    block.erase(unique(block.begin(), block.end()), block.end());
                    blocks.push_back(move(block));
                }
            } else if (tin[to] < tin[vertex]) {
                edgeStack.push_back(edge);
                low[vertex] = min(low[vertex], tin[to]);
            }
        }
        if (parentEdge == -1 && children <= 1) articulation[vertex] = false;
    }

    // Articulation nodes come first, followed by component nodes.
    void build() {
        for (int vertex = 0; vertex < n; ++vertex) if (tin[vertex] == -1) {
            if (graph[vertex].empty()) blocks.push_back({vertex});
            else dfs(vertex, -1);
        }
        int nodes = 0;
        for (int vertex = 0; vertex < n; ++vertex)
            if (articulation[vertex]) position[vertex] = nodes++;
        int blockStart = nodes;
        nodes += blocks.size();
        tree.assign(nodes, {});
        for (int block = 0; block < (int)blocks.size(); ++block)
            for (int vertex : blocks[block]) {
                int blockNode = blockStart + block;
                if (articulation[vertex]) {
                    int jointNode = position[vertex];
                    tree[jointNode].push_back(blockNode);
                    tree[blockNode].push_back(jointNode);
                } else {
                    position[vertex] = blockNode;
                }
            }
    }
};
