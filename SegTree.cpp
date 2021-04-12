template<class T> struct SegTree {
    int size;
    vector<T> values;
    vector<T> operations;
    const T NO_OPERATION = 0;
    const T NEUTRAL_ELEMENT = 0;
    
    SegTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        values.assign(2*size, 0);
        operations.assign(2*size, NO_OPERATION);
    }

    void modify_op(T &a, T b, int len) {
        a = a + b*len;
    }

    T calc_op(T a, T b) {
        return a + b;
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = (lx < a.size()) ? a[lx] : 0);
        int m = (lx + rx) >> 1;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
    void build(vector<T> &a) { build(a, 0, 0, size); }

    void set(int i, T v, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = v);
        int m = (lx + rx) >> 1;
        if (i < m) {
            set(i, v, 2*x + 1, lx, m);
        } else {
            set(i, v, 2*x + 2, m, rx);
        }
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        modify_op(operations[2*x + 1], operations[x], 1);
        modify_op(operations[2*x + 2], operations[x], 1);
        modify_op(values[2*x + 1], operations[x], m - lx);
        modify_op(values[2*x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }
 
    void modify(int l, int r, T v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return;
        if (l <= lx && rx <= r) {
            modify_op(operations[x], v, 1);
            modify_op(values[x], v, rx - lx);
            return;
        }
        propagate(x, lx, rx);
        int m = (lx + rx) >> 1;
        modify(l, r, v, 2*x + 1, lx, m);
        modify(l, r, v, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }
    void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

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
