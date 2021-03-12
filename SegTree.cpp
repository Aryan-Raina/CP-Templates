struct SegTree {
    int size;
    vector<int> values;
    vector<int> operations;
    const int NO_OPERATION = 0;
    const int NEUTRAL_ELEMENT = -1;
    
    void modify_op(int &a, int b, int len) {
        a = a | b;
    }

    int calc_op(int a, int b) {
        return a & b;
    }

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        values.assign(2*size, 0);
        operations.assign(2*size, NO_OPERATION);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = a[lx]);
        int m = (lx + rx) >> 1;
        build(a, 2*x + 1, lx, m);
        build(a, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }

    void build(vector<int> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = v);
        int m = (lx + rx) >> 1;
        if (i < m) {
            set(i, v, 2*x + 1, lx, m);
        } else {
            set(i, v, 2*x + 2, m, rx);
        }
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void propogate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        modify_op(operations[2*x + 1], operations[x], 1);
        modify_op(operations[2*x + 2], operations[x], 1);
        modify_op(values[2*x + 1], operations[x], m - lx);
        modify_op(values[2*x + 2], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }
 
    void modify(int l, int r, int v, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || l >= rx) return;
        if (l <= lx && rx <= r) {
            modify_op(operations[x], v, 1);
            modify_op(values[x], v, rx - lx);
            return;
        }
        int m = (lx + rx) >> 1;
        modify(l, r, v, 2*x + 1, lx, m);
        modify(l, r, v, 2*x + 2, m, rx);
        values[x] = calc_op(values[2*x + 1], values[2*x + 2]);
    }

    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        propogate(x, lx, rx);
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return values[x];
        int m = (lx + rx) >> 1;
        int s1 = calc(l, r, 2*x + 1, lx, m);
        int s2 = calc(l, r, 2*x + 2, m, rx);
        return calc_op(s1, s2);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};
