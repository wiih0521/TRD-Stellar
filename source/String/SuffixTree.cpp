// Online suffix tree (Ukkonen). Append a unique sentinel to expose every suffix.
// Edges store half-open intervals [l, r) in s. O(n log alphabet).
struct SuffixTree {
    struct Node {
        int l, r, parent, link = -1;
        map<char, int> next;
        Node(int l = 0, int r = 0, int p = -1) : l(l), r(r), parent(p) {}
        int len() const { return r - l; }
    };
    struct State { int v, pos; };

    string s;
    vector<Node> tree;
    State active{0, 0};

    explicit SuffixTree(string str) : s(move(str)) {
        tree.reserve(2 * s.size() + 1);
        tree.emplace_back(0, 0, -1);
        tree[0].link = 0;
        for (int i = 0; i < (int)s.size(); ++i) extend(i);
    }

    int child(int v, char c) const {
        auto it = tree[v].next.find(c);
        return it == tree[v].next.end() ? -1 : it->second;
    }
    State go(State st, int l, int r) const {
        while (l < r) {
            if (st.pos == tree[st.v].len()) {
                st = {child(st.v, s[l]), 0};
                if (st.v == -1) return st;
            } else {
                if (s[tree[st.v].l + st.pos] != s[l]) return {-1, -1};
                int take = min(r - l, tree[st.v].len() - st.pos);
                st.pos += take; l += take;
            }
        }
        return st;
    }
    int split(State st) {
        if (st.pos == tree[st.v].len()) return st.v;
        if (st.pos == 0) return tree[st.v].parent;
        Node edge = tree[st.v];
        int mid = (int)tree.size();
        tree.emplace_back(edge.l, edge.l + st.pos, edge.parent);
        tree[edge.parent].next[s[edge.l]] = mid;
        tree[mid].next[s[edge.l + st.pos]] = st.v;
        tree[st.v].parent = mid;
        tree[st.v].l += st.pos;
        return mid;
    }
    int getLink(int v) {
        if (tree[v].link != -1) return tree[v].link;
        if (tree[v].parent == -1) return 0;
        int to = getLink(tree[v].parent);
        int skip = tree[v].parent == 0;
        return tree[v].link = split(go({to, tree[to].len()},
                                      tree[v].l + skip, tree[v].r));
    }
    void extend(int pos) {
        while (true) {
            State next = go(active, pos, pos + 1);
            if (next.v != -1) { active = next; return; }
            int mid = split(active);
            int leaf = (int)tree.size();
            tree.emplace_back(pos, (int)s.size(), mid);
            tree[mid].next[s[pos]] = leaf;
            active.v = getLink(mid);
            active.pos = tree[active.v].len();
            if (mid == 0) break;
        }
    }

    bool contains(const string& pattern) const {
        if (pattern.empty()) return true;
        if (s.empty()) return false;
        State st = go({0, 0}, 0, 0);
        int v = 0, at = 0, i = 0;
        while (i < (int)pattern.size()) {
            if (at == tree[v].len()) {
                v = child(v, pattern[i]); at = 0;
                if (v == -1) return false;
            }
            int take = min((int)pattern.size() - i, tree[v].len() - at);
            for (int k = 0; k < take; ++k)
                if (pattern[i + k] != s[tree[v].l + at + k]) return false;
            i += take; at += take;
        }
        return true;
    }
};
