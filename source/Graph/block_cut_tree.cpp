/*
Usage:
- generate_block_cut_tree(): duh, also return number of vertices
- cc[u]: vertices inside block u
- sz[u]: number of vertices, -1 if is joint
*/


const int N = 1e5 + 69;
int n, m;
vector<int> graph[N], dfs_tree[N];
 
int num[N], low[N];
bool isJoint[N];
vector<int> st;
int dfs_cnt;
vector<vector<int>> bbc;
 
void tarjan(int u, int p){
    num[u] = low[u] = ++dfs_cnt;
 
    vector<int> child;
    for(int v: graph[u]) {
        if (v == p) {p = -1; continue;}
        if (num[v]){
            minimize(low[u], num[v]);
        }
        else{
            child.push_back(v);
            tarjan(v, u);
            minimize(low[u], low[v]);
            if (low[v] >= num[u]){
                isJoint[u] = true;
            }
        }
    }
    if (u == p) isJoint[u] = isJoint[u] && (child.size() >= 2);
    for(int v: child){
        if (isJoint[u] && low[v] >= num[u]) dfs_tree[u].push_back(-v);
        else dfs_tree[u].push_back(v);
    }
}
 
void get_block(int u){
    st.push_back(u);
    for(int v: dfs_tree[u]){
        get_block(abs(v));
        if (v < 0){
            bbc.push_back({});
            while(bbc.back().empty() || bbc.back().back() != abs(v)){
                bbc.back().push_back(st.back());
                st.pop_back();
            }
            bbc.back().push_back(u);
        }
    }
}
 
vector<int> bc_tree[2*N];
int joint_cnt = 0;
int pos[2*N];
int sz[2 * N];
vector<int> cc[2 * N];
 
int generate_block_cut_tree(){
    dfs_cnt = 0;
    for(int i= 1; i<=n; ++i) if (num[i] == 0){
        tarjan(i, i);
        get_block(i);
        if (st.size()) {
            bbc.push_back(st);
            st.clear();
        }
    }
 
    int idx = 0;
    for(int i= 1; i<=n; ++i){
        if (!isJoint[i]) continue;
        joint_cnt++;
        pos[i] = ++idx;
        cc[idx].push_back(-i);
        sz[idx] = 1;
    }
 
    for(vector<int> i: bbc){
        ++idx;
        sz[idx] = i.size();
        cc[idx] = i;
        for(int j: i){
            if (isJoint[j]){
                int u = idx, v = pos[j];
                sz[v]--;
                bc_tree[u].push_back(v);
                bc_tree[v].push_back(u);
            }
        }
    }
    return idx;
}
