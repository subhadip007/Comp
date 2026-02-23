#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)

vector<int> tree[200001] ;
int ans = 0;

int diameter[200001];
//downPath[i] : longest simple path in subtree rooted at i that starts at i
int downPath[200001];
 
void eval_downPaths(int src, int par)
{
    int bestChildDownPath = 0;
    bool leaf = 1;
    for(int child : tree[src])
    {
        if(child != par)
        {
            leaf = 0;
            eval_downPaths(child, src);
            bestChildDownPath = max(bestChildDownPath, downPath[child]);
        }
    }
    if(leaf)downPath[src] = 0;
    else downPath[src] = 1 + bestChildDownPath;
}
 
void solve(int src, int par)
{
    int ans = 0;
    vector<int> childrenDownPaths;
    for(int child : tree[src])
    {
        if(child != par)
        {
            solve(child, src);
            childrenDownPaths.push_back(downPath[child]);
            ans = max(ans, diameter[child]);
        }
    }
    int numOfchildren = childrenDownPaths.size();
    sort(all(childrenDownPaths));
 
    if(numOfchildren == 0)diameter[src] = 0;
    else if(numOfchildren == 1)diameter[src] = 1 + childrenDownPaths[0];
    else diameter[src] = 2+childrenDownPaths[numOfchildren - 1]+childrenDownPaths[numOfchildren - 2];
 
    diameter[src] = max(diameter[src], ans);
}

int main() {
   long long t,n,m,x,i,j,k,q;
   //cin >> t;
   t = 1;
   while(t--)
   {
        cin >> n;
        fr(0,n-1)
        {
            int u,v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        eval_downPaths(1,0);
        solve(1,0);
        cout << diameter[1];
   }
   return 0;
}