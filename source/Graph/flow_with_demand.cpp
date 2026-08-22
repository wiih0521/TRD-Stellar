/*
Usage: 
 - Dependency: Dinic template.
 - FlowWithDemand(n, s, t): initialize a graph of size n, with s and t being the source and sink nodes, respectively
 - add_edge(u, v, d, w): add an edge from u to v, with capacity w, and demand d. 
 - try_edge(capacity): verify whether there exists a flow, such that the total residue is <= capacity.
*/

struct FlowWithDemand {
    int n, s, t, fake_s, fake_t;
    vector<long long> balance;
    Dinic dinic;

    FlowWithDemand(int n, int source, int sink) 
        : n(n), s(source), t(sink), fake_s(n), fake_t(n + 1), balance(n, 0), dinic(n + 2, n, n + 1) {}

    void add_edge(int u, int v, long long demand, long long capacity) {
        balance[u] -= demand;
        balance[v] += demand;
        dinic.add_edge(u, v, capacity - demand);
    }

    bool try_flow(long long capacity) {
        vector<int> extras;
        for (int i = 0; i < n; ++i) {
            if (balance[i] > 0) {
                dinic.add_edge(fake_s, i, balance[i]);
                extras.push_back(fake_s);
                extras.push_back(i);
            } else if (balance[i] < 0) {
                dinic.add_edge(i, fake_t, -balance[i]);
                extras.push_back(fake_t);
                extras.push_back(i);
            }
        }
        extras.push_back(s); extras.push_back(t);
        dinic.add_edge(t, s, capacity);

        bool valid = dinic.max_flow() >= accumulate(balance.begin(), balance.end(), 0LL, [](long long sum, long long x) {
            return sum + max(0LL, x);
        });

        for(int i: extras) {
            dinic.adj[i].pop_back();
        }

        return valid;
    }
};

