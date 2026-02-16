#include <iostream>
#include <algorithm> // for sort, mainly
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <array>
#include <string>
#include <cstdio>
#include <iterator>
#include <unordered_set>
#include <cstdint> // for int64_t, int32_t, etc
#include <queue>
#include <stack>
#include <deque>
#include <numeric> // gcd, lcm
#include <fstream>
#include <bitset> // for bitset
#include <iomanip>
#include <cassert> // for set with custom ordering
#include <type_traits> // for set with custom ordering
#include <utility> // for swap, forward, etc
using namespace std;
 
#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
//#pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
// square root decomposition template, tested for
// CSES Range Update Queries
// https://cses.fi/problemset/task/1651
 
/*
 
increase each value in range [a,b] by u
what is the value at position k?
 
*/
 
typedef int64_t ll;
 
class sqrtdecomp{
 
    private:
        
        ll n;
        ll sq;
        vector<ll> v;
        vector<ll> s; // extra value of every element in the segment
        vector<ll> len; 
        // length of each segment (only really important for the last one)
        // but easier to preprocess like this
 
    public:
 
        void build(ll size, vector<ll> input) {
 
            n = size;
            sq = sqrtl(n);
            if(sq * sq < n) {
                sq++;
            }
            v.resize(n, 0);
            s.resize(sq, 0);
            len.resize(sq, 0);
 
            for(ll i = 0; i < sq; i++) {
                for(ll j = i * sq; j < min((i+1) * sq, n); j++) {
 
                    v[j] = input[j];
                    len[i]++;
                }
            }
        }
 
        void debug() {
            cerr << "\nn=" << n;
            cerr << "\nsq=" << sq;
            cerr << "\nv=" << v;
            cerr << "\ns=" << s;
            cerr << "\nlen=" << len;
        }
 
        void inc(ll l, ll r, ll x) {
 
            ll segl = l / sq;
            ll segr = r / sq;
 
            //cerr << "\nsegl=" << segl;
            //cerr << "\nsegr=" << segr;
 
            if(segl == segr) {
                for(ll i = l; i <= r; i++) {
                    v[i] += x;
                }
 
            }else{
 
                for(ll i = l; i < sq * (segl + 1); i++) {
                    v[i] += x;
                }
                //cerr << "\nsum after left=" << sum;
 
                for(ll i = sq * segr; i <= r; i++) {
                    v[i] += x;
                }
                //cerr << "\nsum after right=" << sum;
 
                for(ll i = segl + 1; i <= segr - 1; i++) {
                    s[i] += x;
                }
                //cerr << "\nsum after mid=" << sum; 
            }
        }
 
        ll query(ll pos) {
 
            //cerr << "\nquery for " << l << " to " << r;
 
            return v[pos] + s[pos/sq];
            
        }
 
};
 
void solve() {
 
    ll n, q;
    cin >> n >> q;
 
    vector<ll> v(n, 0);
    for(ll i = 0; i < n; i++) {
        cin >> v[i];
    }
 
    sqrtdecomp sq;
    sq.build(n, v);
    //sq.debug();
 
    for(ll qi = 0; qi < q; qi++) {
        ll t;
        cin >> t;
 
        if(t == 1) {
            ll a, b, x;
            cin >> a >> b >> x;
            sq.inc(a - 1, b -1, x);
        }else{
 
            ll pos;
            cin >> pos;
 
            cout << sq.query(pos - 1) << "\n";
        }
 
        //cerr << "\nafter operation " << qi;
        //sq.debug();
    }
 
}
 
int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);
 
	solve();
 
	return 0;
}

/*

Written for CSES Range Update Queries

https://cses.fi/problemset/task/1651

Given an array of n integers, your task is to process q queries of the following types:

increase each value in range [a,b] by u
what is the value at position k?

*/