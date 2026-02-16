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

typedef int64_t ll;

// Sparsetable RMQ template written for CSES Static Range Minimum Queries

class sparsetable{

    private:
        ll n;
        ll lim;
        vector<vector<ll>> v;
        vector<ll> p2;

    public:

        void init(ll size, vector<ll> input) {
            
            n = size;

            lim = ceil(log2(n));
            if(pow(2, lim) == n) {
                lim++;
            }
            v.resize(lim, vector<ll>(n, 0));
            // v[power of two][starting position]
            p2.resize(lim); // powers of two, because I dislike bit-shifting

            ll r = 1;

            for(ll i = 0; i < lim; i++) {
                p2[i] = r;
                r *= 2;
            }

            for(ll i = 0; i < size; i++) {
                v[0][i] = input[i];
            }

            for(ll p = 1; p < lim; p++) {

                for(ll i = 0; i + p2[p] - 1 < n; i++) {

                    v[p][i] = min(v[p-1][i], v[p-1][i + p2[p-1]]);
                }
            }
        }

        ll query(ll l, ll r) {

            //cerr << "\nquery, l=" << l << "; r=" << r;

            ll intlen = r - l + 1;
            ll intp = log2(intlen);

            //cerr << "\nintlen=" << intlen;
            //cerr << "\nintp=" << intp;

            return min(v[intp][l], v[intp][r - p2[intp] + 1]);

        }

        void debug() {

            cerr << "\nv=" << v;
        }

};

void solve() {

    ll n, q;
    cin >> n >> q;
    vector<ll> v(n, 0);
    for(ll i = 0; i < n; i++) {
        cin >> v[i];
    }

    sparsetable st;
    st.init(n, v);

    //st.debug();

    for(ll qi = 0; qi < q; qi++) {
        ll a, b;
        cin >> a >> b;
        cout << st.query(a - 1, b - 1) << "\n";
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
