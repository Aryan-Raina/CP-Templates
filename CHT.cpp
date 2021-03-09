struct CHT {
    struct Line {
        int m, c;
        Line(int m, int c) : m(m), c(c) {}
        ld intersect(Line other) { return (ld) (c - other.c)/(other.m - m); }
        int at(int x) { return m*x + c; }
    };

    deque<Line> dq;

    void add(int m, int c) {
        Line newLine(m, c);
        while (dq.size() >= 2 && end(dq)[-2].intersect(newLine) <= end(dq)[-2].intersect(end(dq)[-1])) {
            dq.pop_back();
        }
        dq.push_back(newLine);
    }

    int query(int x) {
        while (dq.size() >= 2 && dq[0].at(x) <= dq[1].at(x)) {
            dq.pop_front();
        }
        return dq[0].at(x);
    }

    int qry(int x) {
        int lo = 0, hi = dq.size()-1, midL, midR;
        while (lo < hi) {
            midL = (lo + hi)>>1;
            midR = midL+1;
            if (dq[midL].at(x) < dq[midR].at(x)) {
                lo = midR;
            } else {
                hi = midL;
            }
        }
        return dq[lo].at(x);
    }
};
