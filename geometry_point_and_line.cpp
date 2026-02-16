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

typedef int64_t ll;

struct point{
	ll x, y;
};

struct eq{
	ll a, b, c;
};

// gets an equation(line) of style ax + by + c = 0, from two points
eq geteq(point a, point b) {

	eq ret;

	ret.a = a.y - b.y;
	ret.b = b.x - a.x;
	ret.c = a.x * (b.y - a.y) - a.y * (b.x - a.x);

	return ret;
}

// tests equation, basically gets the constant difference
// if zero, point is present
ll testeq(eq e, point p) {

	//cerr << "\ntesteq, p={" << p.x << ";" << p.y << "}";

	ll loc = e.a * p.x + e.b * p.y + e.c;
	if(loc == 0) {
		//cerr << " -> 0";
		return 0;
	}else if(loc > 0) {
		//cerr << " -> -1";
		return -1;
	}else if(loc < 0) {
		//cerr << " -> 1";
		return 1;
	}

	return loc;
}

// checks whether point c is present on the segment {a, b} 
bool point_onsegment(point a, point b, point c) {

	//cerr << "\nonsegment, p={" << c.x << ";" << c.y << "}"; 

    eq e = geteq(a, b);

	if(testeq(e, c) != 0) {
		//cerr << " -> false";
		return false;
	}

	if(b.x < a.x) {
		if(c.x >= b.x && c.x <= a.x) {
			//cerr << " -> true";
			return true;
		}
	}else if(a.x < b.x) {
		if(c.x >= a.x && c.x <= b.x) {
			//cerr << " -> true";
			return true;
		}
	}else if(a.x == b.x) {

		if(b.y < a.y) {
			if(c.y >= b.y && c.y <= a.y) {
				return true;
			}
		}else if(b.y > a.y) {
			if(c.y >= a.y && c.y <= b.y) {
				return true;
			}
		}

	}

	//cerr << " -> false";
	return false;
}

// checks whether segments {a1, a2} and {b1, b2} collide
bool collision_of_segments(point a1, point a2, point b1, point b2) {

	eq e1, e2;
	e1 = geteq(a1, a2);
	e2 = geteq(b1, b2);
 
	// hat ez egy ket ismeretlenes egyenletrendszer
	// a1x + b1y + c1 = 0 <-> a1x + b1y = -c1
	// a2x + b2y + c2 = 0 <-> a2x + b2y = -c2
	// nagyon standard, fogja az ember
 
	// tehat az elsot beszorozzuk a2-vel, a masodikat a1-el, kiesik az x, megkapjuk az y-t 
	// es akkor azt visszahelyettesitjuk, megkapjuk az x-et?
 
	if(point_onsegment(a1, a2, b1) || point_onsegment(a1, a2, b2) || point_onsegment(b1, b2, a1) || point_onsegment(b1, b2, a2)) {
		return true;
	}
 
	if(testeq(e1, b1) != testeq(e1, b2) && testeq(e2, a1) != testeq(e2, a2)) {
		return true;
	}
 
	return false;
 
}

// get a point on a line, knowing its x coordinate
// be careful 'cause it's not very precise, I recommend giving it an x divisible by e.b
point getoneq(eq e, ll xcord) {

	ll by = (-e.a * xcord) - e.c;

	point ret;

	ret.x = xcord;

	if(e.b == 0) {
		ret.y = e.c;
	}else{
		ret.y = by/e.b;
	}

	return ret;
}	

// checks whether the segment {a, b} collides with the line/equation e
bool collision_segment_line(point a, point b, eq e) {

    if(testeq(e, a) != testeq(e, b)) {
		return true;
	}

    return false;

}

void solve() {

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);

	solve();

	return 0;
}
