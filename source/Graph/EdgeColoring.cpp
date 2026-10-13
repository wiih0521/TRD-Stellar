// (Delta+1)-colors a simple undirected graph. O(VE).
// Returns the color of each input edge, numbered from 0.
vector<int> edgeColoring(int n, const vector<pair<int, int>>& edges) {
    vector<int> colorsAtVertex(n + 1), result(edges.size()), fan(n), freeColor(n);
    for (auto edge : edges)
        ++colorsAtVertex[edge.first], ++colorsAtVertex[edge.second];
    int colorCount = *max_element(colorsAtVertex.begin(), colorsAtVertex.end()) + 1;
    vector<vector<int>> adjacent(n, vector<int>(colorCount, -1));
    for (auto edge : edges) {
        int u = edge.first, v = edge.second;
        fan[0] = v;
        vector<int> location(colorCount);
        int at = u, end = u, color = freeColor[u], index = 0, i = 0;
        int d;
        while ((d = freeColor[v]), !location[d]
                && (v = adjacent[u][d]) != -1) {
            location[d] = ++index;
            colorsAtVertex[index] = d;
            fan[index] = v;
        }
        colorsAtVertex[location[d]] = color;
        for (int current = d; at != -1;
                current ^= color ^ d, at = adjacent[at][current])
            swap(adjacent[at][current],
                 adjacent[end = at][current ^ color ^ d]);
        while (adjacent[fan[i]][d] != -1) {
            int left = fan[i], right = fan[++i], other = colorsAtVertex[i];
            adjacent[u][other] = left;
            adjacent[left][other] = u;
            adjacent[right][other] = -1;
            freeColor[right] = other;
        }
        adjacent[u][d] = fan[i];
        adjacent[fan[i]][d] = u;
        for (int vertex : {fan[0], u, end}) {
            freeColor[vertex] = 0;
            while (adjacent[vertex][freeColor[vertex]] != -1)
                ++freeColor[vertex];
        }
    }
    for (int i = 0; i < (int)edges.size(); ++i) {
        int u = edges[i].first, v = edges[i].second;
        while (adjacent[u][result[i]] != v) ++result[i];
    }
    return result;
}
