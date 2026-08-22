
const int MOD = 1e9 + 9;
 
ll fast_pow(ll a, ll n){
    ll ans = 1;
    while(n > 0){
        if (n & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        n /= 2;
    }
    return ans;
}
 
ll inverse(ll a){return fast_pow(a, MOD - 2);}
 
ll normie(ll x){
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

vector<ll> solve(vector<vector<ll>> sigma){
    int n = sigma.size(),m = sigma[0].size() - 1;
    vector<bool> banned(n);
    for(int j = 0; j<m; ++j){
        int idx = -1;
        for(int i = 0; i<n; ++i) if (!banned[i] && sigma[i][j]) {
            idx = i; 
            ll head = sigma[i][j];
            ll inv = inverse(head);
            for(int k = 0; k <= m; ++k) sigma[i][k] = (sigma[i][k] * inv) % MOD;
        }
        if (idx == -1) continue;
        banned[idx] = true;
        for(int i = 0; i<n; ++i) if (sigma[i][j] && i != idx){
            for(int k = 0; k <= m; ++k) sigma[i][k] = normie(sigma[i][k] - sigma[idx][k]);
        }
    }
 
    vector<int> deg(n);
    for(int i = 0; i<n; ++i){
        deg[i] = m;
        for(int j = 0; j < m; ++j) if (sigma[i][j]){
            deg[i] = j;
            break;
        }
    }
    for(int i = 0; i<n; ++i){
        if (deg[i] == m) continue;
        while(true){
            int v = m;
            for(int j = deg[i] + 1; j < m; ++j) if (sigma[i][j]){
                v = j;
                break;
            }
            if (v == m) break;
            for(int x = 0; x < n; ++x) if (deg[x] == v){
                ll shit = inverse(sigma[x][v]) * sigma[i][v] % MOD;
                for(int j = 0; j <= m; ++j) {
                    sigma[i][j] = normie(sigma[i][j] - shit * sigma[x][j]);
                }
                break;
            }
        }
    }
    vector<ll> ans(m);
    for(int i = 0; i<n; ++i) {
        ans[deg[i]] = sigma[i].back();
    }
    return ans;
}