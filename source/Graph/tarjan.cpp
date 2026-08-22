/*
Usage:
- dfs(u, p): dfs, what the fuck
- topo[u]: the strongly connected component that u belongs to, sorted topologically.
*/


int n, m;
vector<int> graph[N];
int num[N], low[N], topo[N];
deque<int> st;
int dfs_cnt = 0, topo_cnt = 0;

void dfs(int u, int p){
    num[u] = low[u] = ++dfs_cnt;
    st.push_back(u);
    int cnt = 0;
    for(int v: graph[u]){
        if (v == p && cnt == 0){cnt++; continue;}
        if (!num[v]){
            dfs(v, u);
            minimize(low[u], low[v]);
        }
        else minimize(low[u], num[v]);
    }

    if (num[u] == low[u]){
        topo_cnt++;
        while(st.back() != u){
            topo[st.back()] = topo_cnt;
            st.pop_back();
        }
        topo[u] = topo_cnt; st.pop_back();
    }
}