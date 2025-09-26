#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:

    vector <vector <int> > buildGraph(vector <vector <int>> &edges){
        int nodes = edges.size() ;
        vector <vector <int>> adj(nodes) ;

        for (auto &it : edges){
            int u = it[0] , v = it[1] ;
            adj[u].push_back(v) ;
            adj[v].push_back(u) ;
        }

        return adj ;
    }
    
    vector<int> dfs_iterative(vector<vector<int>> &adj) {
        int nodes = adj.size();
        vector<int> ans;
        vector<int> vis(nodes, 0);
        stack<int> st;

        st.push(0);
        vis[0] = 1;

        while (!st.empty()) {
            int curr = st.top();
            st.pop();
            ans.push_back(curr);

            for (auto &adjNode : adj[curr]) {
                if (!vis[adjNode]) {
                    vis[adjNode] = 1;
                    st.push(adjNode);
                }
            }
        }
        return ans;
    }

    vector <int> dfs_recursive (vector <vector <int>> &adj){
        int n = adj.size() ;
        vector <int> vis(n , 0) ;
        vector <int> ans ;

        
        function<void(int)> dfs = [&](int node) {
            vis[node] = 1;
            ans.push_back(node);
            
            for (auto &adjNode : adj[node]) {
                if (!vis[adjNode]) {
                    dfs(adjNode);
                }
            }
        };
        
        for (int i = 0 ; i < n ; i++){
            if (vis[i]) continue;

            dfs(i) ;
        }
        
        return ans ;
    }
};

void printAns(vector <int> &arr){
    for (auto &it : arr) cout << it << " " ;
    cout << endl;
}

int main() {

    vector<vector<int>> adj = {{1,2}, {0,2,3}, {0,4}, {1,4}, {2,3}};

    Solution obj;
    vector <int> ans = obj.dfs_iterative(adj);
    printAns(ans);
    vector <int> arr = obj.dfs_recursive(adj) ;
    printAns(arr) ;

    return 0;
}