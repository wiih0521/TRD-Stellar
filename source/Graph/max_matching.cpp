struct HopcroftKarp {
    int leftSize, rightSize;
    vector<vector<int>> graph;
    vector<int> leftMatch, rightMatch, distance;

    HopcroftKarp(int leftSize, int rightSize)
        : leftSize(leftSize), rightSize(rightSize), graph(leftSize),
          leftMatch(leftSize, -1), rightMatch(rightSize, -1),
          distance(leftSize) {}

    void addEdge(int left, int right) { graph[left].push_back(right); }

    bool bfs() {
        queue<int> queue;
        fill(distance.begin(), distance.end(), -1);
        for (int left = 0; left < leftSize; ++left)
            if (leftMatch[left] == -1)
                distance[left] = 0, queue.push(left);
        bool found = false;
        while (!queue.empty()) {
            int left = queue.front();
            queue.pop();
            for (int right : graph[left]) {
                int next = rightMatch[right];
                if (next == -1) found = true;
                else if (distance[next] == -1)
                    distance[next] = distance[left] + 1, queue.push(next);
            }
        }
        return found;
    }

    bool dfs(int left) {
        for (int right : graph[left]) {
            int next = rightMatch[right];
            if (next == -1
                    || (distance[next] == distance[left] + 1 && dfs(next))) {
                leftMatch[left] = right;
                rightMatch[right] = left;
                return true;
            }
        }
        distance[left] = -1;
        return false;
    }

    int maxMatching() {
        int result = 0;
        while (bfs())
            for (int left = 0; left < leftSize; ++left)
                if (leftMatch[left] == -1 && dfs(left)) ++result;
        return result;
    }
};
