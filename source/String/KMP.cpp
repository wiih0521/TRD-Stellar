// Prefix function and all occurrences of pattern in text. O(n + m).
vector<int> prefixFunction(const string& s) {
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmpMatch(const string& text, const string& pattern) {
    if (pattern.empty()) {
        vector<int> ans(text.size() + 1);
        iota(ans.begin(), ans.end(), 0);
        return ans;
    }
    vector<int> pi = prefixFunction(pattern), ans;
    for (int i = 0, j = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == (int)pattern.size()) {
            ans.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}
