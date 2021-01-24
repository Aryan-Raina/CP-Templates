struct SegTree {
    int N;
    vector<int> values;
    int NEUTRAL = 0;
    
    int single(int v) {
        return v;
    }

    int merge(int a, int b) {
        return (a+b);
    }

    void init(int n) {
        N = n;
        values.resize(4*n);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = single(a[lx]));
        int mid = (lx + rx)/2;
        build(a, 2*x + 1, lx, mid);
        build(a, 2*x + 2, mid, rx);
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }

    void build(vector<int> &a) {
        init(a.size());
        build(a, 0, 0, N);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = single(v));
        int mid = (lx + rx)/2;
        if (i < mid) {
            set(i, v, 2*x + 1, lx, mid);
        } else {
            set(i, v, 2*x + 2, mid, rx);
        }
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }

    void set(int val, int pos) {
        set(val, pos, 0, 0, N);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return NEUTRAL;
        if (l <= lx && rx <= r) return values[x];
        int mid = (lx + rx)/2;
        int s1 = calc(l, r, 2*x + 1, lx, mid);
        int s2 = calc(l, r, 2*x + 2, mid, rx);
        return merge(s1, s2);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, N);
    }
};
