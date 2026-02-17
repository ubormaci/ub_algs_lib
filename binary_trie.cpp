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
// #pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")

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

cout << fixed << setprecision(n);

set with custom ordering
set<ll, decltype(&cmp)> qu(cmp);

*/

typedef int32_t ll;

class binary_trie{

	private:

		const ll maxp = 30;
		ll nxt = maxp+1;

		vector<vector<ll>> v;
		vector<ll> cnt; // how many nodes of this type exist?
		vector<ll> vl;
		//vector<ll> pw;
		vector<ll> par;
		//vector<bool> e;
		vector<ll> tp;

		void getbin(ll h, vector<ll> &bin) {

			bin.assign(maxp, 0);
			ll c = h;
			ll j = 0;
			while(c > 0) {
				if(c % 2 == 1) {
					bin[j] = 1;
				}
				j++;
				c /= 2;
			}
		}

	public:

		void init() {
			v.assign(maxp+1, vector<ll>(2, -1));
			cnt.assign(maxp+1, 1);
			vl.assign(maxp+1, 0);
			//pw.assign(maxp+1, 0);
			par.assign(maxp+1, 0);
			//e.assign(maxp+1, true);
			tp.assign(maxp+1, 1);

			for(ll i = 0; i <= maxp; i++) {
				vl[i] = 0;
				//pw[i] = i;
				if(i < maxp) {
					par[i] = i+1;
				}
				if(i > 0) {
					v[i][0] = i-1;
					tp[i] = 2 * tp[i-1];
				}
			}
		}

		void ins(ll val) {

			// we get its binary form

			vector<ll> bin;
			getbin(val, bin);
			// we do from up to down
			// and find the final value

			// we go down
			// once we see, that the next type of character doesn't exist, we create it

			//cerr << "\nins=" << val;
			//cerr << "\nbin=" << bin;

			ll curr = maxp;
			cnt[curr]++;
			for(ll i = maxp-1; i>= 0; i--) {

				//cerr << "\ni=" << i << "; bin[i]=" << bin[i];
				//cerr << "\nch=" << v[curr];

				if(v[curr][bin[i]] == -1) {
					// the next position doesn't exist, uh-huh

					v[curr][bin[i]] = nxt;
					v.push_back(vector<ll>(2, -1));
					cnt.push_back(1);
					vl.push_back(bin[i]);
					//pw.push_back(i);
					par.push_back(curr);
					//e.push_back(true);
					curr = nxt;
					nxt++;

				}else{
					// it exists, we jump to it

					curr = v[curr][bin[i]];
					cnt[curr]++;
				}

			}

		}

		void rem(ll val) {

			// we do the traversal, as if an insertion
			// but instead, we'll track the road and decrement the counter
			// with occassional deletions also

			vector<ll> bin;
			getbin(val, bin);

			ll curr = maxp;
			vector<ll> path(1, curr);
			for(ll i = maxp-1; i>= 0; i--) {

				//cerr << "\ni=" << i << "; bin[i]=" << bin[i];
				//cerr << "\nch=" << v[curr];

				curr = v[curr][bin[i]];
				path.push_back(curr);
			}

			// we trace back the path, and decrease count
			// if count becomes zero, we "delete" the node
			// by setting the parent's path towards it to zero
			// and this is where it comes in handy that we know for each node its actual value
			// (or not that much, actually)

			//cerr << "\nrem=" << val << "; path=" << path;

			for(const auto & p : path) {
				cnt[p]--;
				if(cnt[p] == 0) {
					// remove it from parent
					ll ph = par[p];
					v[ph][vl[p]] = -1;
				}
			}

		}

		ll query(ll val) {

			ll curr = maxp;
			vector<ll> bin;
			getbin(val, bin);

			ll ret = 0;

			for(ll i = maxp-1; i>= 0; i--) {
				// tehat most a curr-ben vagyunk
				// es nezzuk, hogy a kovetkezo lepesben hova lephetunk
				
				// az i az maga a kovetkezo lepes
				// ha a kovetkezo lepesben letezik bin[i]-vel ellentetes, odalepunk
				// maskepp az azonosra lepunk

				if(v[curr][1 - bin[i]] != -1) {
					// opposite exists, hell yeah
					ret += tp[i];
					curr = v[curr][1 - bin[i]];
				}else{
					// oh well, we're not getting this
					curr = v[curr][bin[i]];
				}
			}

			return ret;
		}

		void debug() {

			for(ll i = 0; i < nxt; i++) {

				//if(!e[i]) { continue; }
				cerr << "\ncurrent " << i << "; children=" << v[i] << "; parent=" << par[i] << "; value=" << vl[i] << /* "; pw=" << pw[i] << */ "; cnt=" << cnt[i];
			}
		}
};


void solve() {
	
	// initialization
	// the first maxp elements are the elements of 0 with 33 bits

	binary_trie bt;
	bt.init();

	ll q;
	cin >> q;

	//ll sz = 0;
	for(ll qi = 0; qi < q; qi++) {
		char type; ll h;
		cin >> type >> h;

		if(type == '+') {
			bt.ins(h);
			//sz++;
		}
		else if(type == '-') {
			bt.rem(h);
			//sz++;
		}else{
			// query
			cout << bt.query(h) << "\n";
		}

		//debug();
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

written for CF706D Vasily's Multiset

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given q queries and a multiset A, initially containing only integer 0. There are three types of queries:

    "+ x" — add integer x to multiset A.
    "- x" — erase one occurrence of integer x from multiset A. It's guaranteed that at least one x is present in the multiset A before this query.
    "? x" — you are given integer x and need to compute the value , i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer x and some integer y from the multiset A.

Multiset is a set, where equal elements are allowed.

*/