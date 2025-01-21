
template<class T> struct SegmentTree {
    int n; vector<T> values; 
    T IDENTITY = 0;
    SegmentTree(int n, int id) : n(n), values(2*n, IDENTITY = id) {}
    T calc_op(T a, T b) { return a + b; }
    void modify(int i, T v) {
       for (values[i += n] = v; i >>= 1; ) 
          values[i] = calc_op(values[2*i], values[2*i + 1]);
    }
    T calc(int l, int r) {
       T rans = IDENTITY, lans = IDENTITY;
       for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
          if (l & 1) lans = calc_op(lans, values[l++]);
          if (r & 1) rans = calc_op(values[--r], rans);
       }
       return calc_op(lans, rans);
    }
};
