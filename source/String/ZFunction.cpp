
/* YEP! IT IS JUST A Z FUNCTION */
//    Time complexity : O(N)

vector<int> ZFunction(const string &S) {
    int n = S.length();
    vector<int> Z(n);
    for (int L = 0, R = 0, i = 1; i < n; ++i) {
        if (i <= R) Z[i] = min(R - i + 1, Z[i - L]);
        while (i + Z[i] < n && S[Z[i]] == S[i + Z[i]]) Z[i]++;
        if (i + Z[i] - 1 > R) L = i, R = i + Z[i] - 1;
    }
    Z[0] = n;
    return Z;
}