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
        vector<ll> lazy;   
        const ll dummy = 0; // change for performed operation as needed
        const ll lazydummy = 0; // some value that *cannot* appear
                                // and or, does not change the answer
                                // for addition, zero suffices

        // how do we combine two elements of the tree?
        ll join(ll a, ll b) {
            return a + b;
        }

        // how do we combine two lazy values on a node?
        void comblazy(ll curr, ll extra) {

            // for addition, we just add them together
            lazy[curr] = lazy[curr] + extra;
        }

        // how does the current node's value change when we apply the lazy value to it?
        void applylazy(ll curr, ll tl, ll tr, ll val) {

            // in case of sum, add the amount of elements * modification
            ll len = tr - tl + 1;
            tree[curr] = tree[curr] + len * val;
            comblazy(curr, val);
        }

        void propagate(ll curr, ll tl, ll tr) {
            // push the lazy operation to the children

            if(lazy[curr] == lazydummy) {
                return;
            }

            // transmit pending changes to children
            if(tl != tr) {
                
                ll mid = (tl + tr)/2;

                applylazy(curr * 2, tl, mid, lazy[curr]);
                applylazy(curr * 2 + 1, mid+1, tr, lazy[curr]);
            }

            lazy[curr] = lazydummy;
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

            // we are at this node
            // we want to apply changes, and then create pending changes
            // for its children
            // (only if there are changes, of course)

            if(l == tl && r == tr) {
                return tree[curr];
            }

            propagate(curr, tl, tr);

            ll mid = (tl + tr)/2;

            ll h = join(q(curr * 2, tl, mid, l, min(r, mid)), q(curr * 2 + 1, mid+1, tr, max(l, mid+1), r));

            return h;
        }

        void u(ll curr, ll tl, ll tr, ll l, ll r, ll val) {

            if(l > r) {
                return;
            }

            //cerr << "\ncurr=" << curr << "; tl=" << tl << "; tr=" << tr << "; l=" << l << "; r=" << r;

            // combine lazy into children, then apply the lazy to this one

            if(tl == l && tr == r) {

                //cerr << "\nwe're covering the segment to be updated";

                // on this node
                // we apply the operation
                // and then, transmit the pending operation to its children

                applylazy(curr, tl, tr, val);

                return;
            }
            else{

                propagate(curr, tl, tr);

                ll mid = (tl + tr)/2;

                u(curr * 2, tl, mid, l, min(r, mid), val);
                u(curr * 2 + 1, mid+1, tr, max(l, mid+1), r, val);

                tree[curr] = join(tree[curr * 2], tree[curr * 2 + 1]);
            }

        }

        void segdbg(ll curr, ll l, ll r) {

            //cerr << "\ncurrent node is " << curr << "; l=" << l << "; r=" << r << ", stored value=" << tree[curr];
            //cerr << "; havelazy=" << havelazy[curr] << "; lazy value=" << lazy[curr];

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
            lazy.assign(4 * n + 1, lazydummy);
            build(1, 0, n-1, inp);
		}

        void debug() {
            segdbg(1, 0, n-1);
        }

		void update(ll l, ll r, ll val) {
            u(1, 0, n-1, l, r, val);
		}

		ll query(ll l, ll r) {
			return q(1, 0, n-1, l, r);
		}

};

void solve() {

	ll n, q;
	cin >> n >> q;

	vector<ll> v(n, 0);
	//cerr << "\nv=" << v;

	segtree st;
	st.init(n, v);
	
    //cerr << "\nstarting state";
	//st.debug();

	for(ll i = 0; i < q; i++) {

		ll type;
		cin >> type;

		if(type == 0) {

			ll l, r, val;
			cin >> l >> r >> val;
			
            l--;
            r--;

            //cerr << "\n\nupdate segment l=" << l << "; r=" << r << "; with value =" << val;
			st.update(l, r, val);

		}else if(type == 1) {

			ll a, b;
			cin >> a >> b;
			
            a--;
            b--;

            //cerr << "\n\nquery segment l=" << a << "; r=" << b;

            ll ans = st.query(a, b);
			cout << ans << "\n";
		}

        //cerr << "\n\ntree situation";
		//st.debug();
	}

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);

	ll t;
    cin >> t;
    for(ll ti = 0; ti < t; ti++) {
        solve();
    }

	return 0;
}

/*

Range-update range-query lazy propagation segment tree
tsted for SPOJ horrible queries
https://www.spoj.com/problems/HORRIBLE/

add a value to all elements in range [l, r]
answer sum of elements in range [l, r]

many thanks to the USACO guide team
https://usaco.guide/plat/RURQ?lang=cpp

*/
