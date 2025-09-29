#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    if (a < b)
        return gcd(b, a);
    return gcd(b, a % b);
}

class Gcd_sparse_table
{
    int n, logN;
    vector<int> arr;
    vector<vector<int>> table;

public:
    Gcd_sparse_table(const vector<int> &a)
    {
        arr = a;
        n = arr.size();
        logN = (n > 0) ? 31 - __builtin_clz(n) : 0;
        table.assign(n, vector<int>(logN + 1, 0));
        build();
    }

    void build()
    {
        // base case (interval length = 1)
        for (int i = 0; i < n; i++)
        {
            table[i][0] = arr[i];
        }

        // build for larger intervals
        for (int j = 1; j <= logN; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                table[i][j] = gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r)
    {
        if (r < l)
            swap(l, r);
        if (l < 0 || r >= n)
            throw out_of_range("Invalid query");

        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);

        return gcd(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

int main()
{
    vector<int> arr = {5, 2, 6, 3, 9, 7, 4};
    Gcd_sparse_table st(arr);

    cout << "query(0, 2) = " << st.query(0, 2) << "\n"; // gcd of [5,2,6] -> 1
    cout << "query(2, 4) = " << st.query(2, 4) << "\n"; // gcd of [6,3,9] -> 3
    cout << "query(4, 6) = " << st.query(4, 6) << "\n"; // gcd of [9,7,4] -> 1

    return 0;
}
