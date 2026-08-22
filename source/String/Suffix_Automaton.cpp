
/* IT IS THE SHORTEST VER I CAN FIND */
// Time complexity : O(N)

struct SuffixAutomaton {
    vector<vector<int>> next;
    vector<int> len, link;
    int last, size;

    SuffixAutomaton(const string &s) {
        size = 1; last = 0;
        len.push_back(0); link.push_back(-1);
        next.push_back(vector<int>(26, -1));
        
        for (char c : s) {
            int cur = size++;
            len.push_back(len[last] + 1);
            next.push_back(vector<int>(26, -1));
            link.push_back(-1);
            
            int p = last;
            while (p != -1 && next[p][c - 'a'] == -1) {
                next[p][c - 'a'] = cur;
                p = link[p];
            }

            if (p == -1) link[cur] = 0;
            else {
                int q = next[p][c - 'a'];
                if (len[p] + 1 == len[q]) link[cur] = q;
                else {
                    int clone = size++;
                    len.push_back(len[p] + 1);
                    next.push_back(next[q]);
                    link.push_back(link[q]);
                    while (p != -1 && next[p][c - 'a'] == q) {
                        next[p][c - 'a'] = clone;
                        p = link[p];
                    }
                    link[q] = link[cur] = clone;
                }
            }
            last = cur;
        }
    }
};