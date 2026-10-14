/*
Usage: - use as if it was integers
*/

const int MOD = 998244353;
struct Modular{
    ll x;
    Modular(ll _x = 0) {
        x = _x % MOD;
        if (x < 0) x += MOD;
    }
    Modular& operator += (Modular y) { 
        x += y.x; if (x >= MOD) x -= MOD;  
        return *this; 
    }
    Modular &operator -= (Modular y) { 
        x -= y.x; if (x < 0) x += MOD; 
        return *this; 
    }
    Modular &operator *= (Modular y) { 
        x *= y.x; if (x >= MOD) x %= MOD; 
        return *this; 
    }

    Modular operator + (Modular y) { Modular tmp = *this; return tmp += y; }
    Modular operator - (Modular y) { Modular tmp = *this; return tmp -= y; }
    Modular operator * (Modular y) { Modular tmp = *this; return tmp *= y; }
 
    // use at your own risk
    bool operator == (Modular y){
        return x == y.x;
    }
    bool operator != (Modular y){
        return x != y.x;
    }
};
ostream& operator << (ostream& out, Modular x){
    out << x.x;
    return out;
}
istream& operator >> (istream& in, Modular& x) {
    in >> x.x;
    return in;
}