
/* THIS SHIT RUN IN O(N) TOO */

struct PalindromeTree{
    const static int K = 26;
    struct Node{
        long child[K], layer, pi;
        Node(long _layer = 0){
            memset(child, -1, sizeof child);
            layer = _layer;
            pi = -1;
        }
    };

    vector<Node> a;

    PalindromeTree(){
        a.push_back(Node(-1)); a.push_back(Node(0));
        a[1].pi = a[0].pi = 0;
    }

    void add_child(long &x, long layer){
        x = a.size();
        a.push_back(Node(layer));
    }

    void build(string s){
        long id = 0;
        s = "#" + s;
        for(long i = 1; i<s.size(); ++i){
            long digit = s[i] - '0';
            long j = id;
            while(j >= 0){
                if (s[i] == s[i - a[j].layer - 1]) break;
                j = a[j].pi;
            }

            if (a[j].child[digit] != -1) {
                id = a[j].child[digit];
                continue;
            }

            add_child(a[j].child[digit], a[j].layer + 2);
            long v = a[j].child[digit];

            if (a[v].layer == 1) j = 1;
            else if (a[v].layer == 2) j = a[0].child[digit];
            else{
                j = a[j].pi;
                while(j >= 0){
                    if (j == 0 || (s[i] == s[i - a[j].layer - 1])) break;
                    j = a[j].pi;
                }
                j = a[j].child[digit];
            }
            a[v].pi = j;
            id = v;
        }
        cout << a.size() - 2 << "\n";
    }
};