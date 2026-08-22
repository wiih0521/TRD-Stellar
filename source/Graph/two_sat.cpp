/*
Usage: 
 - TwoSAT(n): initialize a graph of size n
 - addDisjunction(u, v): u and v = true
 - solve(): check if it's correct
*/

struct TwoSAT {
    int n, time = 0, sccCount = 0;
    vector<vector<int>> adj;
    vector<int> low, ids, scc;
    vector<bool> onStack;
    vector<int> assignment, st;
 
    TwoSAT(int n) : n(n) {
        adj.resize(2 * n);
        low.assign(2 * n, -1);
        ids.assign(2 * n, -1);
        scc.assign(2 * n, -1);
        onStack.assign(2 * n, false);
        assignment.resize(n);
        st.reserve(2 * n);
    }
 
    inline void addDisjunction(int u, int v) {
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
    }
 
    void tarjanDFS(int v) {
        ids[v] = low[v] = time++;
        st.push_back(v);
        onStack[v] = true;
 
        for (int u : adj[v]) {
            if (ids[u] == -1)
                tarjanDFS(u);
            if (onStack[u])
                low[v] = min(low[v], low[u]);
        }
 
        if (ids[v] == low[v]) {
            while (true) {
                int u = st.back();
                st.pop_back();
                onStack[u] = false;
                scc[u] = sccCount;
                if (u == v) break;
            }
            ++sccCount;
        }
    }
 
    bool solve() {
        for (int i = 0; i < 2 * n; ++i)
            if (ids[i] == -1)
                tarjanDFS(i);
         for (int i = 0; i < n; ++i) {
            if (scc[2 * i] == scc[2 * i + 1])
                return false;
            assignment[i] = (scc[2 * i] < scc[2 * i + 1]);
        }
        return true;
    }
};
