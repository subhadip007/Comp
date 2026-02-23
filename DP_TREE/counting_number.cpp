#include <bits/stdc++.h>
using namespace std;

    long long dp[20][11][2][2];
    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long solve(string& s, int n, int prev,bool leading,
                    bool tight) {
        if (n == 0) {
            return 1;
        }
        
        if(prev!=-1&&dp[n][prev][leading][tight]!=-1) return dp[n][prev][leading][tight];
    
        int ul = tight ? s[s.size() - n] - '0' : 9;
        long long res = 0;
        for (auto it : digits) {
            if (it > ul)
                break;
            bool new_leading = leading && (it == 0);
            bool new_tight = (tight && (it == ul));
            if (new_leading || it!=prev) {
                res += solve(s, n - 1, new_leading ? prev : it, new_leading, new_tight);
            }
        }
        if(prev!=-1){
            dp[n][prev][leading][tight] = res;
        }
        return res;
}

int main() {
    long long l,r;
    cin>>l>>r;
    memset(dp, -1, sizeof(dp));
    
    string R = to_string(r);
    long long Rcnt = solve(R,R.size(),-1,true,true);
    long long Lcnt = 0;

        memset(dp, -1, sizeof(dp));
        --l;
        string L = to_string(l);
        Lcnt = solve(L,L.size(),-1,true,true);
    
    
    cout<<(Rcnt-Lcnt)<<'\n';
    return 0;
}