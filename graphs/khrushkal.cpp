#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdint>
 
// krushkal with (homegrown) DSU, implemented for CSES: Road Reparation
// https://cses.fi/problemset/result/12850239/

#pragma GCC optimize("O2")
 
using namespace std;
 
typedef int64_t ll;
 
void solve() {
 
    ll n, m;
    cin >> n >> m;
 
    vector<pair<ll,pair<ll,ll>>> v(m, {0,{0,0}});
    for(ll i = 0; i < m; i++) {
        cin >> v[i].second.first >> v[i].second.second >> v[i].first;
    }
 
    sort(v.begin(), v.end());
 
    vector<ll> compof(n+1, -1);
    vector<vector<ll>> comps;
    ll compscounter = 0;
 
    ll cost = 0;
 
    for(ll i = 0; i < m; i++) {
        ll costhere = v[i].first;
        ll a = v[i].second.first;
        ll b = v[i].second.second;
 
        bool kept = true;
 
        if(compof[a] == -1 && compof[b] == -1) {
            compof[a] = compscounter;
            compof[b] = compscounter;
            vector<ll> temp;
            temp.push_back(a);
            temp.push_back(b);
            comps.push_back(temp);
            compscounter++;
        }else if(compof[a] == compof[b] && compof[a] != -1) {
            // ugyanaz a comp
            // lekezelt eset, nem tortenik semmi
            kept = false;
        }else if(compof[a] != -1 && compof[b] == -1) {
            compof[b] = compof[a];
            comps[compof[a]].push_back(b);
        }else if(compof[a] == -1 && compof[b] != -1) {
            compof[a] = compof[b];
            comps[compof[b]].push_back(a);
        }else {
            // a es b mindketto egy komponens resze, de kulonbozo komponenseke
            // a nagyobb komponenst a kisebbe olvasszuk
            if(comps[compof[a]].size() >= comps[compof[b]].size()) {
                // b merged into a
                ll prevcomp = compof[b];
                for(const auto & inb : comps[prevcomp]) {
                    compof[inb] = compof[a];
                    comps[compof[a]].push_back(inb);
                }
                comps[prevcomp].clear();
            }else{
                // a merged into b
                ll prevcomp = compof[a];
                for(const auto & ina : comps[prevcomp]) {
                    compof[ina] = compof[b];
                    comps[compof[b]].push_back(ina);
                }
                comps[prevcomp].clear();
            }
        }
 
        if(kept) {
            cost += costhere;
        }
    }
 
    // check for connectivity
    for(ll i = 1; i <= n; i++) {
        if(compof[i] == -1 || compof[i] != compof[1]) {
            cout << "IMPOSSIBLE";
            return;
        }
    }
 
    cout << cost;
 
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    solve();
}