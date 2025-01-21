
struct SegTree {
    typedef T; 
    T NEUTRAL = 0;
    int N;
    vector<T> values;
 
    SegTree(int n) : N(n), values(4*n, NEUTRAL) {}
 
    T merge(T a, T b) {
        T res = a+b;
        return res;
    }
 
    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = (lx < a.size()) ? a[lx] : NEUTRAL;
            return;
        }
        int mid = (lx + rx)/2;
        build(a, 2*x + 1, lx, mid);
        build(a, 2*x + 2, mid, rx);
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }
 
    void build(vector<int> &a) {
        build(a, 0, 0, N);
    }
 
    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = v;
            return;
        }
        int mid = (lx + rx)/2;
        if (i < mid) {
            set(i, v, 2*x + 1, lx, mid);
        } else {
            set(i, v, 2*x + 2, mid, rx);
        }
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }
 
    void set(int pos, int val) {
        set(pos, val, 0, 0, N);
    }
 
    T calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return NEUTRAL;
        if (l <= lx && rx <= r) return values[x];
        int mid = (lx + rx)/2;
        return merge(calc(l, r, 2*x + 1, lx, mid), calc(l, r, 2*x + 2, mid, rx));
    }
 
    T calc(int l, int r) {
        return calc(l, r, 0, 0, N);
    }
};
