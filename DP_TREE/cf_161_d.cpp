#include <bits/stdc++.h>
using namespace std;

#define max_range 50001
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<vector<int>> dp(max_range,vector<int>(501,0));
vector<int> tree[max_range];
vector<vector<int>> cdCnt(max_range,vector<int>(501,0)); //because the K is within 500 we can use a 2d matrix up here
int n,k;
long long res=0;


//This is the trickey part to do the dfs to find all the count of nodes within the range of k
//for each node
void clac_cdcnt(int src,int par){
    for(auto it:tree[src]){
        if(it!=par) clac_cdcnt(it,src);
    }
    cdCnt[src][0] = 1;
    for(int i=1;i<=k;i++){
        cdCnt[src][i] = 0;
        for(auto node:tree[src]){
            if(node!=par){
                cdCnt[src][i]+=cdCnt[node][i-1];
            }
        }
    }
}

void calc(int src, int par){
    dp[src] = cdCnt[src];
    if(par != 0){
        dp[src][1] += 1;
        for(int i = 2; i <= k; i++){
            dp[src][i] += (dp[par][i-1] - cdCnt[src][i-2]);
        }
    }
    res += dp[src][k];
    for(auto it : tree[src]){
        if(it == par) continue;
        calc(it, src);
    }
}

int main() {
    
    
    cin >> n>> k;
   
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    clac_cdcnt(1, 0);
    calc(1, 0);
    cout<<res/2;
    return 0;
}