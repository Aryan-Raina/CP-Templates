struct UFDS {
    vector<int> p; int cc;
    UFDS(int n) : p(n,-1), cc(n) {}
    int fin(int v) { return p[v] < 0 ? v : p[v] = fin(p[v]); }
    bool join(int a, int b) {
        a = fin(a), b = fin(b);
        if (a == b) return false; --cc;
        if (-p[a] < -p[b]) swap(a, b);
        p[a] += p[b]; p[b] = a; return true;
    }
};
