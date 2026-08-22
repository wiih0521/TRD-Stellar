/*
 Usage: FastIO in; in.init(); in >> n;
*/

struct FastIO{
    string buffer;
    vector<ll> king;
    void init(ll _n = 0){
        getline(cin, buffer, '\0');
        buffer += "\n";
        king.reserve(_n);
        ll cur = 0;
        for(char c: buffer){
            if (c <= '9' && c >= '0'){
                if (cur == -1) cur = 0;
                cur = cur * 10 + (c - '0');
            }
            else{
                if (cur != -1) king.push_back(cur);
                cur = -1;
            }
        }
        
        reverse(ALL(king));
    }
    
    template <class T>
    FastIO& operator >> (T &x){
        x = 0;
        if (king.empty()) return *this;
        x = king.back(); king.pop_back();
        return *this;
    }

    bool isEmpty(){return king.empty();}
};