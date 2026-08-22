/*
    KMP template
*/

struct KMP{
    struct Node{
        array<int, 2> nxt;
        int pi;
        Node(){nxt[0] = nxt[1] = 0;pi = -1;}
    };

    int n;
    vector<Node> a;

    KMP(string s){
        n = s.size();
        a.resize(n+1);
        s = "#" + s;
        for(int i = 0; i<n; ++i){
            if (i < n){
                a[i + 1].pi = a[i].nxt[s[i+1] - '0'];
                a[i].nxt[s[i+1] - '0'] = i + 1;
                a[i+1].nxt = a[a[i + 1].pi].nxt;
            }
        }
    }

    int count_matches(string s){
        if (s.size() < n) return 0;
        int x = 0;
        int ans = 0;
        for(char c: s){
            x = a[x].nxt[c - '0'];
            if (x == n) ans++;
        }
        return ans;
    }
};