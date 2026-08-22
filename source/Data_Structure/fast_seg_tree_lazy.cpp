struct SegmentTree{
    int n, h;
    vector<int> t, d;
 
    SegmentTree(int _n){
        n = _n;
        h = logOf(n);
        t.resize(n * 2 + 2), d.resize(n * 2 + 2);
        for(int i = 1; i <= n * 2 + 1; ++i) t[i] = d[i] = 0;
    }
 
    void apply(int p, int value) {
        t[p] += value;
        if (p < n) d[p] += value;
    }
 
    void build(int p) {
        while (p > 1) p >>= 1, t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
    }
 
    void push(int p) {
      for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
          apply(i<<1, d[i]);
          apply(i<<1|1, d[i]);
          d[i] = 0;
        }
      }
    }
 
    void update(int l, int r, int value) {
      l += n, r += n+1;
      int l0 = l, r0 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
      }
      build(l0);
      build(r0 - 1);
    }
 
    int get() {
        int l = 1, r = n;
      l += n, r += n+1;
      push(l);
      push(r - 1);
      int res = INF;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = min(res, t[l++]);
        if (r&1) res = min(t[--r], res);
      }
      return res;
    }
};