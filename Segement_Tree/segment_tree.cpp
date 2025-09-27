#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int n;
    vector<int> segTree;
    vector<int> arr;

public:
    SegmentTree(vector<int> &Arr) {
        n = Arr.size();
        arr = Arr;
        segTree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            segTree[node] = arr[start];
            return;
        }

        int mid = start + (end - start) / 2;
        build(2*node + 1, start, mid);        // left child
        build(2*node + 2, mid + 1, end);     // right child

        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }

    int query(int l, int r) {
        return getAns(l, r, 0, n - 1, 0);
    }

    int getAns(int l, int r, int start, int end, int node) {
        // complete overlap
        if (l <= start && r >= end) {
            return segTree[node];
        }
        // no overlap
        if (end < l || r < start) {
            return 0;
        }
        // partial overlap
        int mid = start + (end - start) / 2;
        return getAns(l, r, start, mid, 2 * node + 1) +
               getAns(l, r, mid + 1, end, 2 * node + 2);
    }

    void update(int idx, int val, int start, int end, int node) {
        if (start == end) {
            segTree[node] = val;
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(idx, val, start, mid, 2 * node + 1);
        } else {
            update(idx, val, mid + 1, end, 2 * node + 2);
        }

        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }

    void update(int idx, int val) {
        update(idx, val, 0, n - 1, 0);
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree st(arr);

    cout << st.query(0, 2) << "\n"; 
    st.update(2, 10);               
    cout << st.query(0, 2) << "\n"; 

    return 0;
}
