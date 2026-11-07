struct SegmentTreeBeats {
    static constexpr ll INF = (1LL << 60);
    struct Node { ll sum, mx, mx2, mxc, mn, mn2, mnc, lz; };
    int n;
    vector<Node> st;

    SegmentTreeBeats(const vector<ll>& a) : n(a.size()), st(4*n) {
        assert(n); build(1, 0, n-1, a);
    }
    void pull(int p) {
        Node &x=st[p], &a=st[p*2], &b=st[p*2+1];
        x.sum=a.sum+b.sum;
        x.mx=max(a.mx,b.mx);
        x.mxc=(a.mx==x.mx?a.mxc:0)+(b.mx==x.mx?b.mxc:0);
        x.mx2=max(a.mx==x.mx?a.mx2:a.mx, b.mx==x.mx?b.mx2:b.mx);
        x.mn=min(a.mn,b.mn);
        x.mnc=(a.mn==x.mn?a.mnc:0)+(b.mn==x.mn?b.mnc:0);
        x.mn2=min(a.mn==x.mn?a.mn2:a.mn, b.mn==x.mn?b.mn2:b.mn);
        x.lz=0;
    }
    void build(int p, int l, int r, const vector<ll>& a) {
        if (l==r) { ll x=a[l]; st[p]={x,x,-INF,1,x,INF,1,0}; return; }
        int m=(l+r)/2;
        build(p*2,l,m,a); build(p*2+1,m+1,r,a); pull(p);
    }
    void addAll(int p, int l, int r, ll x) {
        Node& a=st[p]; a.sum+=(r-l+1)*x;
        a.mx+=x; if (a.mx2!=-INF) a.mx2+=x;
        a.mn+=x; if (a.mn2!=INF) a.mn2+=x;
        a.lz+=x;
    }
    void capMax(int p, ll x) { // chmin
        Node& a=st[p]; if (x>=a.mx) return;
        a.sum+=(x-a.mx)*a.mxc;
        if (a.mn==a.mx) a.mn=x;
        else if (a.mn2==a.mx) a.mn2=x;
        a.mx=x;
    }
    void capMin(int p, ll x) { // chmax
        Node& a=st[p]; if (x<=a.mn) return;
        a.sum+=(x-a.mn)*a.mnc;
        if (a.mx==a.mn) a.mx=x;
        else if (a.mx2==a.mn) a.mx2=x;
        a.mn=x;
    }
    void push(int p, int l, int r) {
        if (l==r) return;
        int m=(l+r)/2;
        addAll(p*2,l,m,st[p].lz); addAll(p*2+1,m+1,r,st[p].lz);
        st[p].lz=0;
        capMax(p*2,st[p].mx); capMax(p*2+1,st[p].mx);
        capMin(p*2,st[p].mn); capMin(p*2+1,st[p].mn);
    }
    void chmin(int ql, int qr, ll x, int p, int l, int r) {
        if (qr<l || r<ql || x>=st[p].mx) return;
        if (ql<=l && r<=qr && x>st[p].mx2) { capMax(p,x); return; }
        push(p,l,r); int m=(l+r)/2;
        chmin(ql,qr,x,p*2,l,m); chmin(ql,qr,x,p*2+1,m+1,r);
        pull(p);
    }
    void chmax(int ql, int qr, ll x, int p, int l, int r) {
        if (qr<l || r<ql || x<=st[p].mn) return;
        if (ql<=l && r<=qr && x<st[p].mn2) { capMin(p,x); return; }
        push(p,l,r); int m=(l+r)/2;
        chmax(ql,qr,x,p*2,l,m); chmax(ql,qr,x,p*2+1,m+1,r);
        pull(p);
    }
    void add(int ql, int qr, ll x, int p, int l, int r) {
        if (qr<l || r<ql) return;
        if (ql<=l && r<=qr) { addAll(p,l,r,x); return; }
        push(p,l,r); int m=(l+r)/2;
        add(ql,qr,x,p*2,l,m); add(ql,qr,x,p*2+1,m+1,r); pull(p);
    }
    ll sum(int ql, int qr, int p, int l, int r) {
        if (qr<l || r<ql) return 0;
        if (ql<=l && r<=qr) return st[p].sum;
        push(p,l,r); int m=(l+r)/2;
        return sum(ql,qr,p*2,l,m)+sum(ql,qr,p*2+1,m+1,r);
    }

    // Public ranges are half-open [l,r).
    void chmin(int l,int r,ll x) { if(l<r) chmin(l,r-1,x,1,0,n-1); }
    void chmax(int l,int r,ll x) { if(l<r) chmax(l,r-1,x,1,0,n-1); }
    void add(int l,int r,ll x) { if(l<r) add(l,r-1,x,1,0,n-1); }
    ll sum(int l,int r) { return l<r?sum(l,r-1,1,0,n-1):0; }
};
