struct UFDS {
    int n;
    vector<int> sz, par;
    void init(int x) {
        n = x;
        par.resize(n+2);
        sz.assign(n+2, 0);
        iota(par.begin(), par.end(), 0);
    }
    int fin(int v) { return par[v] == v ? v : par[v] = fin(par[v]); }
    bool join(int a, int b) {
        a = fin(a); b = fin(b);
        if(a == b) return false;
        if(sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a]+=sz[b];
        return true;
    }
};
