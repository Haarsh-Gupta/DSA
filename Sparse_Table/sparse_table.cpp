#include <bits/stdc++.h>
using namespace std;

class SparseTable {
public:
    int n, logN;
    vector<int> arr;
    vector<vector<int>> table;

    SparseTable(const vector<int>& a) {
        arr = a;
        n = (int)arr.size();
        logN = (n > 0) ? (31 - __builtin_clz(n)) : 0;
        table.assign(n, vector<int>(logN + 1, INT_MAX));
        build();
    }

    void build() {
        if (n == 0) return;
        // j = 0 (interval length = 1)
        for (int i = 0; i < n; ++i) table[i][0] = arr[i];

        // build for larger intervals: length = 1<<j
        for (int j = 1; j <= logN; ++j) {
            int len = 1 << j;
            for (int i = 0; i + len <= n; ++i) {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

   
    int query(int l, int r) {
        if (n == 0) throw out_of_range("Empty array");
        if (l < 0) l = 0;
        if (r >= n) r = n - 1;
        if (l > r) swap(l, r);

        int len = r - l + 1;
        int k = 31 - __builtin_clz(len); 
        
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }

    
    void print() {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " => ";
            for (int j = 0; j <= logN; ++j) {
                if (i + (1 << j) <= n) cout << table[i][j] << ", ";
                else cout << "-, ";
            }
            cout << "\n";
        }
    }
};

int main() {
    vector<int> arr = {5, 2, 6, 3, 1, 7, 4};
    SparseTable st(arr);

    st.print();
    cout << "query(0, 2) = " << st.query(0, 2) << "\n"; // min of [5,2,6] -> 2
    cout << "query(2, 4) = " << st.query(2, 4) << "\n"; // min of [6,3,1] -> 1
    cout << "query(4, 6) = " << st.query(4, 6) << "\n"; // min of [1,7,4] -> 1

    return 0;
}
