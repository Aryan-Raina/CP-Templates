template<class T> struct SparseSegTree {
    int size, CNT = 1;
    vector<T> values, operations, lc, rc;
    const T NO_OPERATION = 0;
    const T NEUTRAL_ELEMENT = 0;
    
    SparseSegTree(int n, int max_nodes) {
        size = 1;
        while (size < n) size <<= 1;
        values.assign(max_nodes, 0);
        operations.assign(max_nodes, NO_OPERATION);
        lc.assign(max_nodes, -1); rc.assign(max_nodes, -1);
    }

    void modify_op(T &a, T b, int len) {
        if (b == NO_OPERATION) return;
        a = b*len;
    }

    T calc_op(T a, T b) {
        return a + b;
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        if (lc[x] == -1) lc[x] = CNT++;
        if (rc[x] == -1) rc[x] = CNT++;
        modify_op(operations[lc[x]], operations[x], 1);
        modify_op(operations[rc[x]], operations[x], 1);
        modify_op(values[lc[x]], operations[x], m - lx);
        modify_op(values[rc[x]], operations[x], rx - m);
        operations[x] = NO_OPERATION;
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[lx] = v);
        propagate();
        int m = (lx + rx) >> 1;
        if (i < m) set(i, v, lc[x], lx, m);
        else set(i, v, rc[x], m, rx);
        values[x] = calc_op(values[lc[x]], values[rc[x]]);
    }
    void set(int i, int v) { set(i, v, 0, 0, size); }
 
    void modify(int l, int r, T v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return;
        if (l <= lx && rx <= r) {
            modify_op(operations[x], v, 1);
            modify_op(values[x], v, rx - lx);
            return;
        }
        propagate(x, lx, rx);
        int m = (lx + rx) >> 1;
        modify(l, r, v, lc[x], lx, m);
        modify(l, r, v, rc[x], m, rx);
        values[x] = calc_op(values[lc[x]], values[rc[x]]);
    }
    void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

    T calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return values[x];
        propagate(x, lx, rx);
        int m = (lx + rx) >> 1;
        return calc_op(calc(l, r, lc[x], lx, m), 
            calc(l, r, rc[x], m, rx));
    }
    T calc(int l, int r) { return calc(l, r, 0, 0, size); }
};
