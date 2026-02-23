#include <bits/stdc++.h>
using namespace std;
 
 
//It stores the sum of the values
int res=0;
 
int doRec(unordered_map<int,vector<int>>& um,int curr,int prev){
    int maxi=0,smax = 0;
    for(auto it:um[curr]){
        if(it==prev) continue;
        int x = doRec(um,it,curr);
        if(x>maxi){
            smax = maxi;
            maxi = x;
        }else if(x>smax){
            smax = x;
        }
    }
    res = max(res,maxi+smax);
    return maxi+1;
}
 
 
int main() {
    int n;
    cin>>n;
    unordered_map<int,vector<int>> um;
   for(int i=1;i<n;i++){
       int u,v;
       cin>>u;
       cin>>v;
       um[u].push_back(v);
       um[v].push_back(u);
   }
    doRec(um,1,-1);
    cout<<res;
    return 0;
}