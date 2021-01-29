struct UFDS {
    int n;
    vector<int> rnk, par;
    void init(int x) {
        n = x;
        par.resize(n+2);
        len.assign(n+2, 1);
        iota(par.begin(), par.end(), 0);
    }
    int fin(int v) { return par[v] == v ? v : par[v] = fin(par[v]); }
    bool join(int a, int b) {
        a = fin(a); b = fin(b);
        if(a == b) return false;
        if(rnk[a] < rnk[b])
            swap(a, b);
        par[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }
};
