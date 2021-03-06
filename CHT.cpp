struct CHT {
    struct Line {
        int m, c;
        Line(int m, int c) : m(m), c(c) {}
        int at(int x) { return m*x + c; }
        ld intersect(Line other) { return (ld) (other.c - c)/(m - other.m); }
    };

    deque<Line> dq;

    void add(int m, int c) {
        Line newLine(m, c);
        while (dq.size() > 1 && dq[1].intersect(newLine) >= dq[1].intersect(dq[0])) {
            dq.pop_front();
        }
        dq.push_front(newLine);
    } 

    int query(int x) {
        while (dq.size() > 1 && dq.back().intersect(end(dq)[-2]) >= x) {
            dq.pop_back();
        }
        return dq.back().at(x);
    }

    int qry(int x) {
        int lo = 0, hi = dq.size()-1, midL, midR;
        while (lo < hi) {
            midL = (lo + hi)>>1;
            midR = midL+1;
            if (dq[midL].at(x) > dq[midR].at(x)) {
                hi = midL;
            } else {
                lo = midR;
            }
        }
        return dq[hi].at(x);
    }
};
