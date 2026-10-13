// Returns {(parent index in result, original vertex)}; root points to itself.
// Requires LCA. Empty subset returns empty. O(k log k).
vector<pair<int, int>> compressTree(const LCA& lca, vector<int> vertices) {
    if (vertices.empty()) return {};
    auto byTin = [&](int a, int b) { return lca.tin[a] < lca.tin[b]; };
    sort(vertices.begin(), vertices.end(), byTin);
    int originalSize = (int)vertices.size();
    for (int i = 0; i + 1 < originalSize; ++i)
        vertices.push_back(lca.lca(vertices[i], vertices[i + 1]));
    sort(vertices.begin(), vertices.end(), byTin);
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
    vector<pair<int, int>> result;
    vector<int> stack, index(lca.parent.size(), -1);
    for (int vertex : vertices) {
        while (!stack.empty() && !lca.ancestor(stack.back(), vertex))
            stack.pop_back();
        int parentIndex = stack.empty() ? (int)result.size()
                                        : index[stack.back()];
        index[vertex] = (int)result.size();
        result.push_back({parentIndex, vertex});
        stack.push_back(vertex);
    }
    return result;
}
