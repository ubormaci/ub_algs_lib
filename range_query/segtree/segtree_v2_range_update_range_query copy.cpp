#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
// #pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")

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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

/*

notes:

int64_t
stoi(string s) -> string to int
to_string() -> int (or else) to string

vector declaration:
vector<ll> v(n, 0)
vector<vector<ll>> v(n, vector<ll>(n, 0));

{if statement} ? {truth value} : {false value}

#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif

std::lcm(ll a, ll b), std::gcd(int a, int b)

cout << fixed << setprecision(n);

set with custom ordering
set<ll, decltype(&cmp)> qu(cmp);

*/

typedef int64_t ll;

class segtree{
	
    // I prefer zero-indexing in the underlying array

	private:
		ll n;
		vector<ll> tree;   
        const ll dummy = 0; // change for performed operation as needed

        ll join(ll a, ll b) {
            return a + b;
        }

        void build(ll curr, ll l, ll r, vector<ll> &inp) {

            if(l == r) {
                tree[curr] = inp[l];
            }else{

                ll mid = (l + r)/2;
                build(curr * 2, l, mid, inp);
                build(curr * 2 + 1, mid+1, r, inp);
                tree[curr] = join(tree[curr * 2], tree[curr * 2 + 1]);
            }
        }

        ll q(ll curr, ll tl, ll tr, ll l, ll r) {

            if(l > r) {
                return dummy;
            }

            if(l == tl && r == tr) {
                return tree[curr];
            }

            ll mid = (tl + tr)/2;

            ll h = join(q(curr * 2, tl, mid, l, min(r, mid)), q(curr * 2 + 1, mid+1, tr, max(l, mid+1), r));

            return h;
        }

        void u(ll curr, ll tl, ll tr, ll l, ll r, ll val) {

            if(tl == tr) {
                tree[curr] = val; // or += val, depending
            }else{

                ll mid = (tl + tr)/2;
                if(pos <= mid) {
                    u(curr * 2, tl, mid, pos, val);
                }else{
                    u(curr * 2 + 1, mid+1, tr, pos, val);
                }

                tree[curr] = join(tree[curr * 2], tree[curr * 2 + 1]);
            }

        }

        void segdbg(ll curr, ll l, ll r) {

            //cerr << "\ncurrent node is " << curr << "; l=" << l << "; r=" << r << ", stored value=" << tree[curr];

            if(l != r) {
                ll mid = (l + r)/2;
                segdbg(curr * 2, l, mid);
                segdbg(curr * 2 + 1, mid+1, r);
            }
        }

	public:

		void init(ll size, vector<ll> inp) {

            n = size;
            tree.assign(4 * n + 1, dummy);
            build(1, 0, n-1, inp);
		}

        void debug() {
            segdbg(1, 0, n-1);
        }

		void update(ll ind, ll val) {
            u(1, 0, n-1, ind, val);
		}

		ll query(ll l, ll r) {
			return q(1, 0, n-1, l, r);
		}

};

void solve() {

	ll n, q;
	cin >> n >> q;

	vector<ll> v(n, 0);
	for(ll i = 0; i < n; i++) {
		cin >> v[i];
	}

	//cerr << "\nv=" << v;

	segtree st;
	st.init(n, v);
	
	st.debug();

	for(ll i = 0; i < q; i++) {
		
		ll type;
		cin >> type;

		if(type == 1) {

			ll ind, val;
			cin >> ind >> val;
			
            ind--;

			st.update(ind, val);

		}else if(type == 2) {

			ll a, b;
			cin >> a >> b;
			
            a--;
            b--;
            
            ll ans = st.query(a, b);
			cout << ans << "\n";
		}

		//st.debug();
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

Range-update range-query lazy propagation segment tree
tsted for CSES Prefix Sum Queries
https://cses.fi/problemset/task/2166


*/
