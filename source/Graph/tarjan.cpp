// Tarjan SCC. component ids are in reverse topological order. O(V+E).
struct SCC {
    vector<vector<int>> graph;
    vector<int> discovery, low, component, stack;
    vector<bool> onStack;
    int timer = 0, componentCount = 0;

    SCC(const vector<vector<int>>& graph)
        : graph(graph), discovery(graph.size(), -1), low(graph.size()),
          component(graph.size(), -1), onStack(graph.size()) {
        for (int vertex = 0; vertex < (int)graph.size(); ++vertex)
            if (discovery[vertex] == -1) dfs(vertex);
    }

    void dfs(int vertex) {
        discovery[vertex] = low[vertex] = timer++;
        stack.push_back(vertex);
        onStack[vertex] = true;
        for (int to : graph[vertex]) {
            if (discovery[to] == -1) {
                dfs(to);
                low[vertex] = min(low[vertex], low[to]);
            } else if (onStack[to]) {
                low[vertex] = min(low[vertex], discovery[to]);
            }
        }
        if (low[vertex] != discovery[vertex]) return;
        while (true) {
            int top = stack.back();
            stack.pop_back();
            onStack[top] = false;
            component[top] = componentCount;
            if (top == vertex) break;
        }
        ++componentCount;
    }
};
