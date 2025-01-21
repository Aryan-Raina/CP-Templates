struct SegTree {
    typedef int T;
    typedef int S;
    int size;
    vector<T> values;
    vector<S> operations;
    const S NO_OPERATION = 1;
    const T NEUTRAL_ELEMENT = 0;
    
    void modify_op(int x, int lx, int rx, S s) {
        (operations[x] *= s)%=MOD;
        (values[x] *= s)%=MOD;
    }
 
    T calc_op(T a, T b) {
        return (a+b)%MOD;
    }
 
    void propogate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        modify_op(2*x+1, lx, m, operations[x]);
        modify_op(2*x+2, m, rx, operations[x]);
        operations[x] = NO_OPERATION;
    }
 
    SegTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        values.assign(2*size, NEUTRAL_ELEMENT);
        operations.assign(2*size, NO_OPERATION);
    }
 
    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = (lx < a.size()) ? a[lx] : NEUTRAL_ELEMENT);
        int m = (lx + rx) >> 1;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
 
    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }
 
    void modify(int l, int r, S v, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || l >= rx) return;
        if (l <= lx && rx <= r) return modify_op(x, lx, rx, v);
        int m = (lx + rx) >> 1;
        modify(l, r, v, 2*x + 1, lx, m);
        modify(l, r, v, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
 
    void modify(int l, int r, S v) {
        modify(l, r, v, 0, 0, size);
    }
 
    T calc(int l, int r, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return values[x];
        int m = (lx + rx) >> 1;
        T s1 = calc(l, r, 2*x + 1, lx, m);
        T s2 = calc(l, r, 2*x + 2, m, rx);
        return calc_op(s1, s2);
    }
 
    T calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};
