template<class T, class O> struct SegmentTree {
    int size;
    vector<T> values;
    vector<O> operations;
    const T NEUTRAL_ELEMENT = 0;
    const O NO_OPERATION = 0;
    
    SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        values.assign(2*size, NEUTRAL_ELEMENT);
        operations.assign(2*size, NO_OPERATION);
    }

    void modify_op(int x, int lx, int rx, O v) {
        values[x].update(v, rx-lx);
        operations[x] = operations[x] + v;
    }

    T calc_op(T a, T b) {
        return a + b;
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = (lx < a.size()) ? a[lx] : NEUTRAL_ELEMENT);
        int m = (lx + rx) >> 1;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
    void build(vector<T> &a) { build(a, 0, 0, size); }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        modify_op(2*x + 1, lx, m, operations[x]);
        modify_op(2*x + 2, m, rx, operations[x]);
        operations[x] = NO_OPERATION;
    }
 
    void modify(int l, int r, O v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return;
        if (l <= lx && rx <= r) return modify_op(x, lx, rx, v);
        propagate(x, lx, rx);
        int m = (lx + rx) >> 1;
        modify(l, r, v, 2*x + 1, lx, m);
        modify(l, r, v, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
    void modify(int l, int r, O v) { modify(l, r, v, 0, 0, size); }

    T calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return values[x];
        propagate(x, lx, rx);
        int m = (lx + rx) >> 1;
        return calc_op(calc(l, r, 2*x + 1, lx, m), 
            calc(l, r, 2*x + 2, m, rx));
    }
    T calc(int l, int r) { return calc(l, r, 0, 0, size); }
};
