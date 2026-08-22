/*
CHT template
*/

const ll INF = 1e18 + 69; 

struct CHT{
    #define Node pair<ll, ll>
    vector<Node> a;
    vector<double> bubble;
    bool flag;

    // if flag = 0: if inserted in increasing order, return min, otherwise return max
    // flag = 1: the opposite
 
    CHT(bool _flag){
        flag = _flag;
    }
 
    double getInter(Node a, Node b){
        double x = (double) (b.second - a.second) / (a.first - b.first);
        return x;
    }
 
    void add(Node x, bool isMin = 1){
        if (a.empty()) {a.push_back(x); return;}
        if (a.back().first == x.first){
            if (isMin) minimize(a[a.size() - 1].second, x.second);
            else maximize(a[a.size() - 1].second, x.second);
            return;
        }
        while(a.size() >= 2){
            double x1 = getInter(a.back(), x), x2 = bubble.back();
            if (flag){
                if (x1 >= x2) break;
            }
            else{
                if (x1 <= x2) break;
            }
            a.pop_back(); bubble.pop_back();
        }
        bubble.push_back(getInter(a.back(), x));
        a.push_back(x);
    }
 
    ll get(ll x){
        if (a.empty()) return INF;
        long idx;
        if (flag) idx = lower_bound(ALL(bubble),x) - bubble.begin();
        else idx = lower_bound(ALL(bubble), x, greater<double>()) - bubble.begin();
        return a[idx].first * x + a[idx].second;
    }
};
