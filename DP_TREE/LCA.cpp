#include <bits/stdc++.h>
using namespace std;

#define max_range 200001
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<int> tree[max_range];
int dp[max_range][20];
int lvl[max_range];

void calc_lvl(int src,int par,int level){
    lvl[src] = level;
    for(auto it:tree[src]){
        if(it!=par){
            calc_lvl(it,src,level+1);
        }
    }
}
void pre_calc(int src,int par){
    dp[src][0] = par;

    for(int i=1;i<20;i++){
        if(dp[src][i-1]!=-1){
            dp[src][i] = dp[dp[src][i-1]][i-1];
        }
        else{
            dp[src][i] = -1;
        }
    }

    for(auto it:tree[src]){
        if(it!=par){
            pre_calc(it,src);
        }
    }
}

int lift_node(int src,int step_jump){
    for(int i=19;i>=0;i--){
        if(step_jump==0||step_jump==-1){
            break;
        }
        
        if(step_jump>=(1<<i)){
            step_jump-=(1<<i);

            //If I have to jump 5 steps
            //First jump 2^2 = 4 steps then from there 2^0 =1 step
            src = dp[src][i];
        }
    }
    return src;
}

int find_lca(int u,int v){
    if(lvl[u]<lvl[v]){
        swap(u,v);
    }
    u = lift_node(u,lvl[u]-lvl[v]);
    if(u==v) return v;

    for(int i=19;i>=0;i--){
        if(dp[u][i]!=dp[v][i]){
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    //we started from the fact that v and u are at same level and we continue checking till when 
    //there is a mismatch the last mismatch we find in thier ancestory
    //we just just 1 nodes from there, bevause after 2 nodes the nodes becomes same so it has to be in between that node
    //So we jump 1 node which is 2^0
    return lift_node(u,1);
}


int main(){
    memset(dp,-1,sizeof(dp));
    int n,q;
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        int x,y;
        cin>>x;
        tree[i].push_back(x);
        tree[x].push_back(i);
    }
    calc_lvl(1,-1,0);
    pre_calc(1,-1);

    for(int i=1;i<=q;i++){
        int node,k;
        cin>>node>>k;
        cout<<find_lca(node,k)<<'\n';
    }
}