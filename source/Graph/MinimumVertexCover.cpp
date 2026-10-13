// Bipartite minimum vertex cover. Returned ids are L: [0,n), R: [n,n+m).
// Requires dfsMatching() above. O(VE).
vector<int> minimumVertexCover(const vector<vector<int>>& graph, int rightSize) {
    int leftSize = (int)graph.size();
    vector<int> rightToLeft(rightSize, -1);
    int matchingSize = dfsMatching(graph, rightToLeft);
    vector<int> reachableLeft(leftSize, true), reachableRight(rightSize);
    for (int left : rightToLeft)
        if (left != -1) reachableLeft[left] = false;
    vector<int> stack;
    for (int left = 0; left < leftSize; ++left)
        if (reachableLeft[left]) stack.push_back(left);
    while (!stack.empty()) {
        int left = stack.back();
        stack.pop_back();
        reachableLeft[left] = true;
        for (int right : graph[left])
            if (!reachableRight[right] && rightToLeft[right] != -1) {
                reachableRight[right] = true;
                stack.push_back(rightToLeft[right]);
            }
    }
    vector<int> cover;
    for (int left = 0; left < leftSize; ++left)
        if (!reachableLeft[left]) cover.push_back(left);
    for (int right = 0; right < rightSize; ++right)
        if (reachableRight[right]) cover.push_back(leftSize + right);
    assert((int)cover.size() == matchingSize);
    return cover;
}
