struct LinkCutNode {
    LinkCutNode *parent = nullptr, *pathParent = nullptr, *child[2];
    bool flipped = false;

    LinkCutNode() { child[0] = child[1] = nullptr; fix(); }

    void fix() {
        if (child[0]) child[0]->parent = this;
        if (child[1]) child[1]->parent = this;
        // Update path aggregates here if needed.
    }

    void push() {
        if (!flipped) return;
        flipped = false;
        swap(child[0], child[1]);
        if (child[0]) child[0]->flipped ^= true;
        if (child[1]) child[1]->flipped ^= true;
    }

    int direction() const {
        return parent ? (parent->child[1] == this) : -1;
    }

    void rotate(int side, int type) {
        int diagonal = side ^ type;
        LinkCutNode* x = child[side];
        LinkCutNode* y = (type == 2 ? x : x->child[diagonal]);
        LinkCutNode* z = type ? y : x;
        y->parent = parent;
        if (parent) parent->child[direction()] = y;
        child[side] = z->child[side ^ 1];
        if (type < 2) {
            x->child[diagonal] = y->child[diagonal ^ 1];
            y->child[diagonal ^ 1] = x;
        }
        z->child[side ^ 1] = this;
        fix(); x->fix(); y->fix();
        if (parent) parent->fix();
        swap(pathParent, y->pathParent);
    }

    void splay() {
        push();
        while (parent) {
            if (parent->parent) parent->parent->push();
            parent->push();
            push();
            int first = direction(), second = parent->direction();
            if (second == -1) parent->rotate(first, 2);
            else parent->parent->rotate(second, first != second);
        }
    }

    LinkCutNode* first() {
        push();
        return child[0] ? child[0]->first() : (splay(), this);
    }
};

struct LinkCutTree {
    vector<LinkCutNode> node;
    LinkCutTree(int n) : node(n) {}

    LinkCutNode* access(LinkCutNode* vertex) {
        vertex->splay();
        while (LinkCutNode* upper = vertex->pathParent) {
            upper->splay();
            vertex->pathParent = nullptr;
            if (upper->child[1]) {
                upper->child[1]->parent = nullptr;
                upper->child[1]->pathParent = upper;
            }
            upper->child[1] = vertex;
            upper->fix();
            vertex = upper;
        }
        return vertex;
    }

    void makeRoot(LinkCutNode* vertex) {
        access(vertex);
        vertex->splay();
        if (vertex->child[0]) {
            vertex->child[0]->parent = nullptr;
            vertex->child[0]->flipped ^= true;
            vertex->child[0]->pathParent = vertex;
            vertex->child[0] = nullptr;
            vertex->fix();
        }
    }

    bool connected(int a, int b) {
        if (a == b) return true;
        LinkCutNode* rootA = access(&node[a])->first();
        LinkCutNode* rootB = access(&node[b])->first();
        return rootA == rootB;
    }

    void link(int a, int b) {
        assert(!connected(a, b));
        makeRoot(&node[a]);
        node[a].pathParent = &node[b];
    }

    void cut(int a, int b) {
        LinkCutNode* first = &node[a];
        LinkCutNode* second = &node[b];
        makeRoot(second);
        first->splay();
        LinkCutNode* upper = first->pathParent
            ? first->pathParent : first->child[0];
        assert(upper == second);
        if (first->pathParent) {
            first->pathParent = nullptr;
        } else {
            first->child[0] = nullptr;
            second->parent = nullptr;
            first->fix();
        }
    }
};
