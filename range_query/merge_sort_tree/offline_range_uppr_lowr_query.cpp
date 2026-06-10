#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
//#pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")

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
#include <unordered_map>
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
 *
 * notes:
 *
 * int64_t
 * stoi(string s) -> string to int
 * to_string() -> int (or else) to string
 *
 * vector declaration:
 * vector<ll> v(n, 0)
 * vector<vector<ll>> v(n, vector<ll>(n, 0));
 *
 * {if statement} ? {truth value} : {false value}
 *
 * set lower bound/upper bound:
 * 	// . . . m1 . . . d . . . . m2
 *    auto m1_it = b.lower_bound(d);
 *    advance(m1_it, -1);
 *    m1 = *m1_it;
 *	m2 = *b.upper_bound(d);
 *
 * #ifdef LOCAL
 *    freopen("in.txt","r",stdin);
 *    freopen("out.txt","w",stdout);
 * #endif
 *
 * constexpr auto lcm(auto x, auto... xs)
 * {
 *	return ((x = std::lcm(x, xs)), ...);
 * }
 *
 * std::gcd(int a, int b)
 *
 * cout << setprecision(n);
 *
 * set with custom ordering
 * set<ll, decltype(&cmp)> qu(cmp);
 *
 */

typedef int32_t ll;

class mergesort_tree{
	
    // I prefer zero-indexing in the underlying array
 
	private:
		ll n;
		vector<vector<ll>> tree;   
        const ll dummy = 0; // change for performed operation as needed
 
        vector<ll> join(const vector<ll>& a, const vector<ll>& b) {
            
            ll an = a.size(), bn = b.size();
            vector<ll> ret(an+bn);

            ll ri = 0;
            ll ai = 0, bi = 0;
            while(ai < an && bi < bn) {

                if(a[ai] <= b[bi]) {
                    ret[ri] = a[ai];
                    ri++;
                    ai++;
                }else{
                    ret[ri] = b[bi];
                    ri++;
                    bi++;
                }
            }
            while(ai < an) {
                ret[ri] = a[ai];
                ri++;
                ai++;
            }
            while(bi < bn) {
                ret[ri] = b[bi];
                ri++;
                bi++;
            }
            return ret;
            
        }

        ll qjoin(ll a, ll b) {
            return a + b;
        }
 
        void build(ll curr, ll l, ll r, vector<ll> &inp) {
 
            if(l == r) {
                tree[curr].push_back(inp[l]);
            }else{
 
                ll mid = (l + r)/2;
                build(curr * 2, l, mid, inp);
                build(curr * 2 + 1, mid+1, r, inp);
                tree[curr] = join(tree[curr * 2], tree[curr * 2 + 1]);
            }
        }
 
        ll q(ll curr, ll tl, ll tr, ll l, ll r, ll val) {
 
            if(l > r) {
                return dummy;
            }
 
            if(l == tl && r == tr) {

                // do a binary search
                // first value which is grater than val

                ll here = 0;
                if(tree[curr][0] > val) {
                    return tree[curr].size();
                }else if(*tree[curr].rbegin() <= val) {
                    return 0;
                }

                // do a binary search
                auto it = upper_bound(tree[curr].begin(), tree[curr].end(), val) - tree[curr].begin();

                here = tree[curr].size() - it;

                return here;
            }
 
            ll mid = (tl + tr)/2;
 
            ll h = qjoin(q(curr * 2, tl, mid, l, min(r, mid), val),q(curr * 2 + 1, mid+1, tr, max(l, mid+1), r, val));
 
            return h;
        }
 
        void segdbg(ll curr, ll l, ll r) {
 
            cerr << "\ncurrent node is " << curr << "; l=" << l << "; r=" << r << ", stored value=" << tree[curr];
 
            if(l != r) {
                ll mid = (l + r)/2;
                segdbg(curr * 2, l, mid);
                segdbg(curr * 2 + 1, mid+1, r);
            }
        }
 
	public:
 
		void init(ll size, vector<ll> &inp) {
 
            n = size;
            tree.resize(4 * n + 1);
            build(1, 0, n-1, inp);
		}
 
        void debug() {
            segdbg(1, 0, n-1);
        }
 
        // count in array [l, r] those higher than val
		ll query(ll l, ll r, ll val) {
			return q(1, 0, n-1, l, r, val);
		}
 
};
 
void solve() {
 
	ll n, q;
    cin >> n >> q;
 
    vector<ll> v(n+1, 0);
	vector<ll> nxt(n+1, n+1);
    
    vector<pair<ll,ll>> srt(n, {0,0});

    for(ll i = 0; i < n; i++) {
        cin >> v[i];
        srt[i] = {v[i], i};
    }

    sort(srt.begin(), srt.end());

    for(ll i = 0; i < n - 1; i++) {
        if(srt[i].first == srt[i+1].first) {
            nxt[srt[i].second] = srt[i+1].second;
        }
    }

    //cerr << "\nv=" << v;
    //cerr << "\nnxt=" << nxt;

	mergesort_tree seg;
	seg.init(n+1, nxt);

	for(ll qi = 0; qi < q; qi++) {
		
		ll l, r;
        cin >> l >> r;
        r--;

        ll cnt = seg.query(l, r, r);
        
        //cerr << "\nmaximum in segment " << l << "; r=" << r << " : " << mx;
        
        cout << cnt << "\n";
 
		//cerr << "\nafter operation " << qi << "; tree situation is=";
		//seg.debug();
	}
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();

    return 0;
}

/*

Static merge sort tree template
tested by CSES Distinct Value Queries https://cses.fi/problemset/result/17499603/
and Yosup Static Range Count Distinct https://judge.yosupo.jp/submission/378421

*/