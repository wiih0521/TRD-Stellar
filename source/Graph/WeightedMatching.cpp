// Minimum-cost matching of every row to a distinct column; rows <= columns.
// Negate costs for maximum weight. O(rows^2 * columns).
template<class T>
pair<T, vector<int>> weightedMatching(const vector<vector<T>>& costMatrix) {
    int rows = (int)costMatrix.size();
    int columns = rows ? (int)costMatrix[0].size() : 0;
    assert(rows <= columns);
    vector<T> distance(columns), potential(columns);
    vector<int> match(rows), reverse(columns, -1), order(columns), previous(columns);
    T total = 0;
    for (int row = rows - 1; row >= 0; --row) {
        for (int column = 0; column < columns; ++column) {
            distance[column] = costMatrix[row][column];
            order[column] = column;
            previous[column] = row;
        }
        int used = 0, freeColumn = -1, matchedRow = -1;
        T delta = 0;
        while (true) {
            for (int j = used; j < columns; ++j) {
                int column = order[j];
                T reduced = distance[column] - potential[column];
                if (j == used || delta > reduced) {
                    delta = reduced;
                    swap(order[used], order[j]);
                }
            }
            freeColumn = order[used++];
            matchedRow = reverse[freeColumn];
            if (matchedRow == -1) break;
            for (int column = 0; column < columns; ++column) {
                T candidate = costMatrix[matchedRow][column]
                            - costMatrix[matchedRow][freeColumn]
                            + distance[freeColumn];
                if (candidate < distance[column]) {
                    distance[column] = candidate;
                    previous[column] = matchedRow;
                }
            }
        }
        total += distance[freeColumn];
        while (used--)
            potential[order[used]] = distance[order[used]] - delta;
        for (; matchedRow != row; swap(freeColumn, match[matchedRow]))
            matchedRow = reverse[freeColumn] = previous[freeColumn];
    }
    return {total, match};
}
