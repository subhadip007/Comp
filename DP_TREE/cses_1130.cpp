#include <bits/stdc++.h>
using namespace std;
long dp[1000000][2];

long solve(vector<vector<int>>& adj,int node,int parent){
    
    if(adj[node].size()==0) return 0;
    
    for(auto it:adj[node]){
        if(it==parent) continue;
        dp[node][0]+=solve(adj,it,node);
    }
    
    for(auto it:adj[node]){
        if(it==parent) continue;
        long x = dp[it][0]>=dp[it][1] ? 0 : dp[it][1]-dp[it][0];
        dp[node][1] = max(dp[node][1],1+dp[node][0]-x);
    }
    
    return max(dp[node][0],dp[node][1]);
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    memset(dp, 0, sizeof(dp));
    cout << solve(adj, 1, -1) << endl;
    
    return 0;
}