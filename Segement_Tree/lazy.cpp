#include <bits/stdc++.h>
using namespace std;

class lazyTree {
    int n;
    vector<int> arr, lazy, segTree;

public:
    lazyTree(vector<int> &a) {
        n = a.size();
        arr = a;
        lazy.resize(4 * n, 0);
        segTree.resize(4 * n, 0);

        build(0, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            segTree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid);
        build(2 * node + 2, mid + 1, end);

        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            segTree[node] += (end - start + 1) * lazy[node];

            if (start != end) { // push lazy to children
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    int query(int l, int r, int node, int start, int end) {
        propagate(node, start, end);

        // no overlap
        if (r < start || l > end) return 0;

        // full overlap
        if (l <= start && end <= r) return segTree[node];

        // partial overlap
        int mid = (start + end) / 2;
        int left_sum = query(l, r, 2 * node + 1, start, mid);
        int right_sum = query(l, r, 2 * node + 2, mid + 1, end);

        return left_sum + right_sum;
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }

    void update(int l, int r, int val, int node, int start, int end) {
        propagate(node, start, end);

        // no overlap
        if (r < start || l > end) return;

        // full overlap
        if (l <= start && end <= r) {
            segTree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        // partial overlap
        int mid = (start + end) / 2;
        update(l, r, val, 2 * node + 1, start, mid);
        update(l, r, val, 2 * node + 2, mid + 1, end);

        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }

    void update(int l, int r, int val) {
        update(l, r, val, 0, 0, n - 1);
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    lazyTree st(arr);

    cout << st.query(0, 4) << "\n"; // 15
    st.update(1, 3, 2);
    cout << st.query(0, 4) << "\n"; // 21
    cout << st.query(2, 4) << "\n"; // 16

    return 0;
}
