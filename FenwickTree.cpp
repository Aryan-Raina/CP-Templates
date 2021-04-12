struct FenwickTree {
    vector<int> s; // s[i] represents sum from [i with last 1 changed to 0, i]
    FenwickTree(int _n) : s(_n) {}
    void modify(int pos, int dif) { // a[pos] += dif
        for (; pos < s.size(); pos |= pos+1) s[pos] += dif; // keep changing last 0 to 1
    } 
    int calc(int pos) { // sum of values in [0, pos)
        int res = 0;
        for (; pos > 0; pos &= pos-1) res += s[pos-1]; // keep changing last 1 to 0
        return res;
    }
};
