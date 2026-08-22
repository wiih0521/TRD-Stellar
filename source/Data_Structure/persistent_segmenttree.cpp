class PersistentSegmentTree {
private:
    int n;
    vector<Node*> roots; // Store roots of different versions

    // Build initial segment tree
    Node* build(int start, int end) {
        if (start == end) return new Node(0); // Initialize with zero; customize as needed
        int mid = (start + end) / 2;
        return new Node(0, build(start, mid), build(mid + 1, end));
    }

    // Create new version with point update
    Node* update(Node* prev, int start, int end, int idx, int val) {
        if (start == end) return new Node(prev->value + val); // Update node value
        int mid = (start + end) / 2;
        if (idx <= mid)
            return new Node(prev->value + val, update(prev->left, start, mid, idx, val), prev->right);
        else
            return new Node(prev->value + val, prev->left, update(prev->right, mid + 1, end, idx, val));
    }

    // Query for a range [L, R]
    int query(Node* node, int start, int end, int L, int R) {
        if (start > R || end < L) return 0; // Return 0 for sum; adjust for other ops
        if (L <= start && end <= R) return node->value;
        int mid = (start + end) / 2;
        return query(node->left, start, mid, L, R) + query(node->right, mid + 1, end, L, R);
    }

public:
    PersistentSegmentTree(int size) : n(size) {
        roots.push_back(build(0, n - 1)); // Initial version
    }

    // Update tree version by creating a new version
    void update(int idx, int val) {
        roots.push_back(update(roots.back(), 0, n - 1, idx, val));
    }

    // Query a specific version
    int query(int version, int L, int R) {
        return query(roots[version], 0, n - 1, L, R);
    }
};