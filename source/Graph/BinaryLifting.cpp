vector<vector<int>> buildJumpTable(const vector<int>& parent) {
    int levels = 1;
    while ((1LL << levels) <= (int)parent.size()) ++levels;
    vector<vector<int>> jump(levels, parent);
    for (int level = 1; level < levels; ++level)
        for (int vertex = 0; vertex < (int)parent.size(); ++vertex)
            jump[level][vertex] = jump[level - 1][jump[level - 1][vertex]];
    return jump;
}

int jumpUp(const vector<vector<int>>& jump, int vertex, int distance) {
    for (int bit = 0; bit < (int)jump.size(); ++bit)
        if (distance & (1LL << bit)) vertex = jump[bit][vertex];
    return vertex;
}

int liftingLca(const vector<vector<int>>& jump,
        const vector<int>& depth, int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    a = jumpUp(jump, a, depth[a] - depth[b]);
    if (a == b) return a;
    for (int level = (int)jump.size() - 1; level >= 0; --level)
        if (jump[level][a] != jump[level][b])
            a = jump[level][a], b = jump[level][b];
    return jump[0][a];
}
