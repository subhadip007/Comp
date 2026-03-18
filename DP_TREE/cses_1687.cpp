#include <bits/stdc++.h>
using namespace std;

#define max_range 200001
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<int> tree[max_range];
int dp[max_range][20];

void pre_calc(int src,int par){

    dp[src][0] = par;

    for(int i=1;i<=19;i++){
        if(dp[src][i-1]!=-1){
            //as 2^x = 2^(x-1)+2^(x-1);
            //So beacuse I filling 2^x I already must have knowed the answer for 2^x-1, Now after how much distance it will compleate 2^x from the
            //staring node the answer is 2^x-1;
            dp[src][i] = dp[dp[src][i-1]][i-1];
        }else{
            dp[src][i]= -1;
        }
    }

    for(auto it:tree[src]){
        if(it!=par){
            pre_calc(it,src);
        }
    }
}

int calc(int node,int k){
    int res = 0;
    for(int i=19;i>=0;i--){
        if(k>=(1<<i)){
            node = dp[node][i];
            if(node==-1) return -1;
            k=(k^(1<<i));
        }
    }

    return node;
}

int main(){
    memset(dp,-1,sizeof(dp));
    int n,q;
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        tree[i].push_back(x);
        tree[x].push_back(i);
    }
    pre_calc(1,-1);
    for(int i=1;i<=q;i++){
        int node,k;
        cin>>node>>k;
        cout<<calc(node,k)<<'\n';
    }
}
