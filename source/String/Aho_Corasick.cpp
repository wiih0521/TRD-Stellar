/*
checked
*/

int nx[N][26];
int suf_link[N], par[N];
int leaf[N];
int num_node = 0;
int exlink[N];


int add(const string& s)
{
    int u = 0;
    for (const char& c : s)
    {
        if (nx[u][c - 'a'] == -1) nx[u][c - 'a'] = ++num_node;
        par[nx[u][c - 'a']] = u;
        u = nx[u][c - 'a'];
    }
    leaf[u] = 1;
    return u;
}
void build()
{
    queue<int> q;
    q.push(0);
    while (sz(q))
    {
        int u = q.front(); q.pop();
        int v = suf_link[u];
        if (leaf[v]) exlink[u] = v;
        else exlink[u] = exlink[v];
        for (int i = 0; i < 26; ++i)
        {
            int x = nx[u][i];
            if (nx[u][i] == -1)
                nx[u][i] = u == 0 ? 0 : nx[v][i];
            else
            {
                suf_link[x] = u == 0 ? 0 : nx[v][i];
                q.push(x);
            }
        }

    }
}