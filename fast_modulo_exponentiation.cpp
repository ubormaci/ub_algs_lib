#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <array>
#include <string>
#include <cstdio>
#include <iterator>
#include <unordered_set>
#include <cstdint>
#include <queue>
#include <stack>
#include <deque>
#include <numeric>
#include <fstream>
using namespace std;

typedef int64_t ll;

ll fastexpmod(ll base, ll pw, ll md) {

    ll p = base;
    ll ret = 1; // return value

    while(pw > 0) {
        if(pw % 2 == 1) {
            ret = (ret * p) % md;
        }

        p = (p * p) % md;
        pw /= 2;
    }

    return ret;
}

void solve() {
    
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	ll tests = 0;
	cin >> tests;

	while(tests--)
	{
		solve();
	}

	return 0;
}
