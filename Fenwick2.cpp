template<class T> struct FenwickTree {
    int size;
    vector<T> s[2], x; 
    // 0 -> [i-lsb+1, i], 1 -> [i, i+lsb-1], lsb - least significant bit 
    const T NEUTRAL = {1,0};
    
    FenwickTree(int n) {
        size = 1; while (size < n) size <<= 1;
        x = vector<T>(size+1, NEUTRAL);
        s[0] = s[1] = x;
        for (int i = 1; i <= n; i++) cin>>x[i][0]>>x[i][1];
        build();
    }
    T comb(T a, T b) {
        return T{a[0]*b[0] % MOD, (a[1]*b[0] % MOD + b[1]) % MOD};
    }
    void build() {
        for (int i = 1; i < size; i++) {
            s[0][i] = comb(s[0][i], x[i]);
            int j = i+(i&-i);
            s[0][j] = comb(s[0][j], s[0][i]);
        }
        for (int i = size-1; i >= 1; i--) {
            s[1][i] = comb(x[i], s[1][i]);
            int j = i-(i&-i);
            s[1][j] = comb(s[1][i], s[1][j]);
        }
    }

    T qry(int l, int r) {
        T lans, rans; lans = rans = NEUTRAL;
        for (; l+(l&-l) <= r; l += l&-l) lans = comb(lans, s[1][l]);
        for (; r-(r&-r) >= l; r -= r&-r) rans = comb(s[0][r], rans);
        return comb(comb(lans, x[l]), rans);
    }

    void upd0(int i) {
        T lans, rans; lans = rans = NEUTRAL;
        for (int pos = i, l = i-1, r = i+1; pos < size; pos += pos&-pos) {
            for (; r < pos; r += r&-r) rans = comb(rans, s[1][r]);
            for (; l > pos-(pos&-pos); l -= l&-l) lans = comb(s[0][l], lans);
            s[0][pos] = comb(lans, x[i]);
            if (pos != i) s[0][pos] = comb(comb(s[0][pos], rans), x[pos]);
        }
    }
    void upd1(int i) {  
        T lans, rans; lans = rans = NEUTRAL;
        for (int pos = i, l = i-1, r = i+1; pos > 0; pos -= pos&-pos) {
            for (; r < pos+(pos&-pos); r += r&-r) rans = comb(rans, s[1][r]);
            for (; l > pos; l -= l&-l) lans = comb(s[0][l], lans);
            s[1][pos] = comb(x[i], rans);
            if (pos != i) s[1][pos] = comb(comb(x[pos], lans), s[1][pos]);
        }
    }
    void upd(int i, T val) {
        x[i] = val, upd0(i), upd1(i);
    }
};
