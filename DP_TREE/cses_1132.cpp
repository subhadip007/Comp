#include <bits/stdc++.h>
using namespace std;
 
#define max_range 200001
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
int depth[max_range];
vector<int> tree[max_range];
vector<vector<pair<int,int>>> dp(max_range,vector<pair<int,int>>(2,{INT_MIN,INT_MIN}));
int res[max_range];

void calculateED(int src, int par, int src_depth){
    if(src_depth > dp[par][0].first){
        dp[par][1] = dp[par][0];
        dp[par][0] = {src_depth, src};
    } else if(src_depth > dp[par][1].first){
        dp[par][1] = {src_depth, src};
    }
}

void eval_depth(int src, int par)
{
    int src_depth = 0;
    for(int child : tree[src])
    {
        if(child != par)
        {
            eval_depth(child, src);
            src_depth = max(src_depth, 1 + depth[child]);
        }
    }
    depth[src] = src_depth;
    calculateED(src, par, depth[src]);
}

void solve(int src, int par, int par_ans){
    for(int child : tree[src]){
        if(child == par) continue;
        
        int findSib;
        if(dp[src][0].second == child){
            findSib = dp[src][1].first;
        } else {
            findSib = dp[src][0].first;
        }
        

        int partial_ans = 1 + max(par_ans, findSib);
        
        solve(child, src, partial_ans);
    }
    
    int best_child = dp[src][0].first;
    res[src] = 1 + max(par_ans, best_child);
}
 
int main() {
    
    int n;
    cin >> n;
   
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    eval_depth(1, 0);
    solve(1, 0, -1);
    
    for(int i = 1; i <= n; i++){
        cout << res[i] << " ";
    }
    
    return 0;
}