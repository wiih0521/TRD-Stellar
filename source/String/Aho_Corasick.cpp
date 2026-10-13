// Multiple pattern matching over ['a', 'z']. Empty patterns are unsupported.
struct AhoCorasick {
    struct Node {
        array<int, 26> next;
        int link = 0;
        vector<int> out;
        Node() { next.fill(-1); }
    };
    vector<Node> trie{1};

    int add(const string& s, int id) {
        assert(!s.empty());
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            assert(0 <= c && c < 26);
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = (int)trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        trie[v].out.push_back(id);
        return v;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int u = trie[0].next[c];
            if (u == -1) trie[0].next[c] = 0;
            else q.push(u);
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            int f = trie[v].link;
            trie[v].out.insert(trie[v].out.end(), trie[f].out.begin(), trie[f].out.end());
            for (int c = 0; c < 26; ++c) {
                int u = trie[v].next[c];
                if (u == -1) trie[v].next[c] = trie[f].next[c];
                else {
                    trie[u].link = trie[f].next[c];
                    q.push(u);
                }
            }
        }
    }

    vector<pair<int, int>> match(const string& text) const {
        vector<pair<int, int>> ans;
        int v = 0;
        for (int i = 0; i < (int)text.size(); ++i) {
            int c = text[i] - 'a';
            assert(0 <= c && c < 26);
            v = trie[v].next[c];
            for (int id : trie[v].out) ans.push_back({i, id});
        }
        return ans;
    }
};
