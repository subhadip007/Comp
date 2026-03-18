#include <bits/stdc++.h>
using namespace std;

#define max_range 200001
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

long depth[max_range];
long childCount[max_range];
vector<int> tree[max_range];
long res[max_range];
int n;
void eval_depth_sum(int src, int par)
{

    for(int child : tree[src])
    {
        if(child != par)
        {
            eval_depth_sum(child, src);
            depth[src] += depth[child] + childCount[child]+1;
            childCount[src]+=1+childCount[child];
        }
    }

}
void solve(int src,int par){

    if (par == 0) {
        res[src] = depth[src];
    } else {
        //as we are going from parent to child all the child of src as well as the src itself is getting
                 //closer by 1 so we are deducting childcount[src] and 1 for the src node itself
                 // then we are adding all the rest of the nodes in the tree as they are getting furthur form the parent by 1
        res[src] = res[par]  
                 - (childCount[src] + 1) 
                 + (n - childCount[src] - 1);
    }
    for (int child : tree[src]) {
        if (child == par) continue;
        solve(child, src);
    }
}
int main() {
    
    
    cin >> n;
   
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    eval_depth_sum(1, 0);
    solve(1, 0);
    
    for(int i = 1; i <= n; i++){
        cout << res[i] << " ";
    }
    
    return 0;
}