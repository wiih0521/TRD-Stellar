// Index of the lexicographically smallest cyclic rotation. O(n).
int minRotation(const string& s) {
    int n = (int)s.size();
    if (n == 0) return 0;
    string t = s + s;
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (t[i + k] == t[j + k]) { ++k; continue; }
        if (t[i + k] > t[j + k]) i += k + 1;
        else j += k + 1;
        if (i == j) ++j;
        k = 0;
    }
    return min(i, j);
}
