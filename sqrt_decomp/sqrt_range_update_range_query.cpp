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
// CSES Range Updates and Sums
// https://cses.fi/problemset/task/1735

/*

Increase each value in range [a,b] by x.
Set each value in range [a,b] to x.
Calculate the sum of values in range [a,b].

*/

typedef int64_t ll;

class sqrtdecomp{

    private:
        
        ll n;
        ll sq;
        vector<ll> v;
        vector<ll> s; // sum of each segment, without the common extra
        vector<ll> e; // each element of segment x
        vector<ll> se; // set each element of segment to x
        vector<ll> len; 
        // length of each segment (only really important for the last one)
        // but easier to preprocess like this

        void applyupdates(ll seg) {

            // same thought process as lazy propagation

            if(se[seg] != -1) {

                for(ll i = sq * seg; i < sq * (seg+1); i++) {
                    v[i] = se[seg];
                }
                se[seg] = -1;
            }
            if(e[seg] != 0) {
                for(ll i = sq * seg; i < sq * (seg+1); i++) {
                    v[i] += e[seg];
                }
                e[seg] = 0;
                return;
            }

        }

    public:

        void build(ll size, vector<ll> input) {

            n = size;
            sq = sqrtl(n);
            if(sq * sq < n) {
                sq++;
            }
            v.resize(n, 0);
            s.resize(sq, 0);
            e.resize(sq, 0);
            se.resize(sq, -1);
            len.resize(sq, 0);

            for(ll i = 0; i < sq; i++) {
                for(ll j = i * sq; j < min((i+1) * sq, n); j++) {

                    v[j] = input[j];
                    s[i] += input[j];
                    len[i]++;
                }
            }
        }

        void debug() {
            cerr << "\nn=" << n;
            cerr << "\nsq=" << sq;
            cerr << "\nv=" << v;
            cerr << "\ns=" << s;
            cerr << "\ne=" << e;
            cerr << "\nse=" << se;
            cerr << "\nlen=" << len;
        }

        void inc(ll l, ll r, ll x) {

            //cerr << "\ndebug before increase ";
            //debug();

            ll segl = l / sq;
            ll segr = r / sq;

            //cerr << "\nsegl=" << segl;
            //cerr << "\nsegr=" << segr;

            if(segl == segr) {
                
                applyupdates(segl);

                for(ll i = l; i <= r; i++) {
                    v[i] += x;
                    s[segl] += x;
                }

            }else{

                applyupdates(segl);
                applyupdates(segr);

                for(ll i = l; i < sq * (segl + 1); i++) {
                    v[i] += x;
                    s[segl] += x;
                }
                //cerr << "\nsum after left=" << sum;

                for(ll i = sq * segr; i <= r; i++) {
                    v[i] += x;
                    s[segr] += x;
                }
                //cerr << "\nsum after right=" << sum;

                for(ll i = segl + 1; i <= segr - 1; i++) {
                    e[i] += x;
                    s[i] += x * len[i];
                }
                //cerr << "\nsum after mid=" << sum; 
            }
        }

        void set(ll l, ll r, ll x) {

            ll segl = l / sq;
            ll segr = r / sq;

            //cerr << "\nsegl=" << segl;
            //cerr << "\nsegr=" << segr;

            if(segl == segr) {
                applyupdates(segl);

                for(ll i = l; i <= r; i++) {
                    ll diff = x - v[i];
                    s[segl] += diff;
                    v[i] = x;
                }

            }else{

                applyupdates(segl);
                applyupdates(segr);
                
                for(ll i = l; i < sq * (segl + 1); i++) {
                    ll diff = x - v[i];
                    s[segl] += diff;
                    v[i] = x;
                }
                //cerr << "\nsum after left=" << sum;

                for(ll i = sq * segr; i <= r; i++) {
                    ll diff = x - v[i];
                    s[segr] += diff;
                    v[i] = x;
                }
                //cerr << "\nsum after right=" << sum;

                for(ll i = segl + 1; i <= segr - 1; i++) {
                    e[i] = 0;
                    se[i] = x;
                    s[i] = x * len[i];
                }
                //cerr << "\nsum after mid=" << sum; 
            }
        }

        ll query(ll l, ll r) {

            //cerr << "\nquery for " << l << " to " << r;

            ll sum = 0;

            ll segl = l / sq;
            ll segr = r / sq;

            //cerr << "\nsegl=" << segl;
            //cerr << "\nsegr=" << segr;

            if(segl == segr) {
                applyupdates(segl);
                
                for(ll i = l; i <= r; i++) {
                    sum += v[i];
                }

            }else{

                applyupdates(segl);
                applyupdates(segr);

                for(ll i = l; i < sq * (segl + 1); i++) {
                    sum += v[i];
                }
                //cerr << "\nsum after left=" << sum;

                for(ll i = sq * segr; i <= r; i++) {
                    sum += v[i];
                }
                //cerr << "\nsum after right=" << sum;

                for(ll i = segl + 1; i <= segr - 1; i++) {
                    sum += s[i];
                }
                //cerr << "\nsum after mid=" << sum; 
            }

            return sum;
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
        }else if(t == 2){
            ll a, b, x;
            cin >> a >> b >> x;
            sq.set(a - 1, b -1, x);
        }else if(t == 3) {

            ll a, b;
            cin >> a >> b;

            ll ans = sq.query(a - 1, b - 1);
            cout << ans << "\n";
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
