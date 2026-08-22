/*
Lichao Tree
*/

const ll INF = 1e18;
 
struct LichaoTree{
    #define Node pair<ll, ll>
 
    long n;
    bool isMin;
    vector<Node> a;
 
    LichaoTree(long _n, bool flag = 1){
        n = _n;
        isMin = flag;
        if (flag) a.resize(n * 4 + 4, make_pair(0, INF));
        else a.resize(n * 4 + 4, make_pair(0, -INF));
    }
 
    ll f(Node t, ll x){return t.first * x + t.second;}
 
    void update(Node x, long l, long r, long id){
        bool check1 = f(a[id], l) >= f(x, l), check2 = f(a[id], r) >= f(x, r);
        bool check3 = f(a[id], l) <= f(x, l), check4 = f(a[id], r) <= f(x, r);
        if (check1 && check2){
            if (isMin) a[id] = x;
            return;
        }
        if (check3 && check4){
            if (!isMin) a[id] = x;
            return;
        }
        if (l == r) return;
        long mid = (l + r) >> 1;
        update(x, l, mid, id * 2);
        update(x, mid + 1, r, id * 2 + 1);
    }
 
    void update(Node x){update(x, 1, n, 1);}
 
    ll get(long i, long l, long r, long id){
        ll ans1 = f(a[id], i);
        if (l == r) return ans1;
        long mid = (l + r) >> 1;
 
        ll ans2;
        if (i <= mid) ans2 = get(i, l, mid, id * 2);
        else ans2 = get(i, mid + 1, r, id * 2 + 1);
 
        if (isMin) return min(ans1, ans2);
        else return max(ans1, ans2);
    }
 
    ll get(long i){return get(i, 1, n, 1);}
};
