/*
    Usage: that's the dsu, push the edges in, and get the chains. Now you have the treeline
*/


struct DSU{
    int n;
    vector<int> parent, sz;
    vector<vector<pair<int, int>>> chain;
 
    DSU(int _n){
        n = _n;
        parent.resize(n+1); sz.resize(n+1, 1);
        chain.resize(n+1);
        for(int i = 0; i<=n; ++i) {
            parent[i] = i;
            chain[i] = {{i, 0}};
        }
    }
 
    int find_set(int u){return (u == parent[u]) ? u : (parent[u] = find_set(parent[u]));}
    bool same_set(int u, int v){return find_set(u) == find_set(v);}
 
    bool join_set(int u, int v, int w){
        u = find_set(u), v = find_set(v);
        if (u != v){
            if (sz[u] < sz[v]) swap(u, v);
            parent[v] = u;
            sz[u] += sz[v];
            chain[v][0].second = w;
            for(pair<int, int> i: chain[v]) chain[u].push_back(i);
            return true;
        }
        return false;
    }
 
    int get_size(int u){return sz[find_set(u)];}
};