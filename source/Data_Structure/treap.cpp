/*
Treap template
*/

struct BST{
    struct Node{
        int val, priority;
        Node* child[2];
        Node(int val): val(val), priority(rngesus(0, MASK(30) - 1)){
            child[0] = child[1] = nullptr;
        }
    };

    Node* root;

    BST(){
        root = nullptr;
    }

    void split(Node* cur, int x, Node* & L, Node*& R){ // split up to a point x
        if (cur == nullptr) {L = R = nullptr;return;}
        if (x < cur -> val){
            split(cur -> child[0], x, L, cur -> child[0]);
            R = cur;
        }
        else{
            split(cur -> child[1], x, cur -> child[1], R);
            L = cur;
        }
    }       

    void merge(Node*& cur, Node* L, Node* R){
        if (L == nullptr) cur = R;
        else if (R == nullptr) cur = L;
        else{
            if (R -> priority > L -> priority) {
                cur = R;
                merge(cur -> child[0], L, R -> child[0]);
            }
            else{
                cur = L;
                merge(cur -> child[1], L -> child[1], R);
            }
        }
    }

    void insert(int x){
        Node *L, *R;
        split(root, x, L, R);
        merge(root, L, new Node(x));
        merge(root, root, R);
    }

    void erase(int x){
        Node *L = nullptr, *mid = nullptr, *R = nullptr;
        split(root, x-1, L, mid);
        split(mid, x, mid, R);

        merge(root, L, R);
    }

    bool find(int x){
        Node *id = root;
        while(true){
            if (id == nullptr) return false;
            if (id -> val == x) return true;
            else if (x < id -> val) id = id -> child[0];
            else id = id -> child[1];
        }
    }

    void clear(){
        while(root != nullptr){
            int val = root -> val;
            erase(val);
        }
    }
};