template<class T> struct Node {
    Node *lc = 0, *rc = 0;
    int lx, rx; T value, operation;
 
    const T NEUTRAL_ELEMENT = 0;
    const T NO_OPERATION = 0;
 
    T calc_op(T a, T b) {
        return a + b;
    }
 
    void modify_op(T &a, T b, int len) {
        if (b == NO_OPERATION) return;
        a = b*len;
    }
 
    Node(int _lx, int _rx) : lx(_lx), rx(_rx) {
        value = NEUTRAL_ELEMENT;
        operation = NO_OPERATION;
    }
    Node(vector<T> &v, int _lx, int _rx) : lx(_lx), rx(_rx) {
        operation = NO_OPERATION;
        if (rx - lx == 1) value = v[lx];
        else {
            int m = (lx + rx) >> 1;
            lc = new Node(v, lx, m), rc = new Node(v, m, rx);
            value = calc_op(lc->value, rc->value);
        }
    }  
 
    void propogate() {
        if (rx - lx == 1) return;
        int m = (lx + rx) >> 1;
        if (!lc) lc = new Node(lx, m);
        if (!rc) rc = new Node(m, rx);
        modify_op(lc->operation, operation, 1);
        modify_op(rc->operation, operation, 1);
        modify_op(lc->value, operation, m-lx);
        modify_op(rc->value, operation, rx-m);
        operation = NO_OPERATION;
    }
 
    void set(int i, int v) {
        if (rx - lx == 1) return void(value = v);
        propogate();
        int m = (lx + rx) >> 1;
        if (i < m) lc->set(i, v);
        else rc->set(i, v);
        value = calc_op(lc->value, rc->value);
    }
 
    void modify(int l, int r, int v) {
        if (l >= rx || lx >= r) return;
        if (l <= lx && rx <= r) {
            modify_op(operation, v, 1);
            modify_op(value, v, rx - lx);
            return;
        }
        propogate();
        lc->modify(l, r, v); rc->modify(l, r, v);
        value = calc_op(lc->value, rc->value);
    }
 
    T calc(int l, int r) {
        if (l >= rx || lx >= r) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return value;
        propogate();
        int x = calc_op(lc->calc(l, r), rc->calc(l, r));
        return x;
    }
};
