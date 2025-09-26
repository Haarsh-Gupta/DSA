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
    
    vector <int> bfs (vector <vector <int>> &adj){
        // int nodes = edges.size() ;
        // vector <vector <int>> adj ;
        // adj = buildGraph(edges) ;

        int nodes = adj.size() ;

        vector <int> ans ;
        vector <int>  vis(nodes , 0) ;
        queue <int> q ;
        q.push(0) ;
        vis[0] = 1 ;

        while (!q.empty()){

            auto curr = q.front() ;
            ans.push_back(curr) ;
            q.pop() ;

            for (auto &adjNode : adj[curr]){
                if (vis[adjNode]) continue;

                vis[adjNode] = 1 ;
                q.push(adjNode) ;
            }
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
    vector <int> ans = obj.bfs(adj);
    printAns(ans);

    return 0;

    return 0;
}