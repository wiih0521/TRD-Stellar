
/*------------------------------ Big num template start ------------------------------*/

string add(string a, string b){
    if (a.size() > b.size()) b = string(a.size() - b.size(), '0') + b;
    if (a.size() < b.size()) a = string(b.size() - a.size(), '0') + a;
    long carry = 0;
    for(long i = a.size() - 1; i>=0; --i){
        a[i] += b[i] - '0' + carry;
        if (a[i] > '9'){
            a[i] -= 10;
            carry = 1;
        }
        else carry = 0;
    }
    if (carry) a = "1" + a;
    return a;
}

string sub(string a, string b){
    if (a.size() > b.size()) b = string(a.size() - b.size(), '0') + b;
    if (a.size() < b.size()) a = string(b.size() - a.size(), '0') + a;
    long carry = 0;
    for(long i = a.size() - 1; i>=0; --i){
        a[i] -= b[i] - '0' + carry;
        if (a[i] < '0'){
            a[i] += 10;
            carry = 1;
        }
        else carry = 0;
    }
    for(long i = 0; i<a.size(); ++i) if (a[i] != '0') return a.substr(i);
    return "0";
}

string mul(string a, ll x){
    if (x == 0) return "0";
    string ans = "";
    ll carry = 0;
    reverse(ALL(a));
    for(auto c: a){
        long digit = c - '0';
        carry += x * digit;
        ans.push_back(carry % 10 + '0');
        carry /= 10;
    }
    while(carry > 0){
        ans.push_back(carry % 10 + '0');
        carry /= 10;
    }
    reverse(ALL(ans));
    return ans;
}

const ll BLOCK = 15;
string mul(string a, string b){
    if (a == "0" || b == "0") return "0";
    string ans = "0";
    for(long i = 0; i<(b.size() + BLOCK - 1) / BLOCK; ++i){
        long e = b.size() - i * BLOCK;
        long s = max(0, e - BLOCK);
        ll cur = 0;
        for(long j = s; j<e; ++j)
            cur = cur * 10 + (b[j] - '0');
        ans = add(ans, mul(a, cur) + string(i * BLOCK, '0'));
    }
    return ans;
}

string fast_pow(string a, ll n){
    if (n == 0) return "1";
    string tmp = fast_pow(a, n/2);
    tmp = mul(tmp, tmp);
    if (n % 2) return mul(tmp, a);
    return tmp;
}

string di(string a, ll x){
    string ans = "";
    ll carry = 0;
    for(char c: a){
        long digit = c - '0';
        carry = carry * 10 + digit;
        ans.push_back('0' + carry / x);
        carry %= x;
    }
    for(long i = 0; i<ans.size(); ++i) if (ans[i] != '0') return ans.substr(i);
    return "0";
}

/*------------------------------ Big num template end ------------------------------*/
