struct SegmentTree{
    int n;
    vector<int> a;

    SegmentTree(int _n){
        n = _n;
        a.resize(n * 2 + 2, -INF);
    }

    void update(int i, int v){
        i += n; if (!maximize(a[i], v)) return;
        while(i > 1){
            i >>= 1;
            a[i] = max(a[i * 2], a[i * 2 + 1]);
        }
    }

    int get(int l, int r){
        l += n; r += n + 1;
        int ans = -INF;
        while(l < r){
            if (l & 1) maximize(ans, a[l++]);
            if (r & 1) maximize(ans, a[--r]);
            l >>= 1; r >>= 1;
        }
        return ans;
    }
};