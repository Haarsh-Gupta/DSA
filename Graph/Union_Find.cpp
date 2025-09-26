#include <bits/stdc++.h>
using namespace std;

class UnionFind {
    vector<int> parent, rank, size;
    int N;

public:
    UnionFind(int n) {
        N = n;
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        rank.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int node) {
        if (parent[node] == node) return node;
        return parent[node] = Find(parent[node]); // path compression
    }

    void Union(int x, int y) {
        int par_x = Find(x);
        int par_y = Find(y);
        if (par_x != par_y) parent[par_x] = par_y;
    }

    void UnionByRank(int x, int y) {
        int par_x = Find(x);
        int par_y = Find(y);

        if (par_x == par_y) return;

        if (rank[par_x] > rank[par_y]) {
            parent[par_y] = par_x;
        } else if (rank[par_x] < rank[par_y]) {
            parent[par_x] = par_y;
        } else {
            parent[par_y] = par_x;
            rank[par_x]++;
        }
    }

    void UnionBySize(int x, int y) {
        int par_x = Find(x);
        int par_y = Find(y);

        if (par_x == par_y) return;

        if (size[par_x] >= size[par_y]) {
            size[par_x] += size[par_y];
            parent[par_y] = par_x;
        } else {
            size[par_y] += size[par_x];
            parent[par_x] = par_y;
        }
    }

    int Component(int start = 0) {
        int count = 0;
        int end = (start == 0 ? N : N + 1);
        for (int i = start; i < end; i++) {
            if (Find(i) == i) count++;
        }
        return count;
    }
};

int main() {
    UnionFind uf(5);

    uf.UnionBySize(1, 2);
    uf.UnionBySize(2, 3);
    uf.UnionByRank(4, 5);

    cout << "Number of components (1-based): " << uf.Component(1) << endl;
    cout << "Number of components (0-based): " << uf.Component(0) << endl;

    return 0;
}
