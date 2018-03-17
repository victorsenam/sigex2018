#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

inline ll rand (ll a, ll b) { return (rand()%(b-a+1))+a; }

struct vec {
	ll x, y;

	inline vec operator + (vec o) const { return {x + o.x, y + o.y}; }
	inline vec operator - (vec o) const { return {x - o.x, y - o.y}; }

	inline bool halfplane () const { return (x > 0) || (x == 0 && y <= 0); }
	inline bool leftOf (vec a, vec b, bool colinear = false) const { vec u = (*this) - a; vec v = b - a; return (u.x*v.y - v.x*u.y < 0) || (colinear && u.x*v.y == v.x*u.y); }
};

// n : vertices on the polygon
// m : points outside the polygon
int main () {
	int n, m, seed;
	ll lim;
	cin >> n >> m >> lim >> seed;
	srand(seed); rand(); rand();

	// generate a convex polygon with n vertices
	// http://cglab.ca/~sander/misc/ConvexGeneration/convex.html
	vector<ll> x(n), y(n);
	for (vector<ll> * v : {&x,&y}) {
		// lim/10 avoids a very big polygon, which is helpful for the fast generation of the m points
		for (int i = 0; i < n; i++) (*v)[i] = rand(-lim/10,lim/10);
		sort(v->begin(), v->end());

		vector<ll> a, b;
		a.pb((*v)[0]); b.pb((*v)[0]);
		for (int i = 1; i < n-1; i++) {
			if (rand(0,1)) a.pb((*v)[i]);
			else b.pb((*v)[i]);
		}
		a.pb((*v)[n-1]); b.pb((*v)[n-1]);
		
		int j = 0; 
		for (int i = 0; i < a.size() - 1; i++)
			(*v)[j++] = a[i+1] - a[i];
		for (int i = 0; i < b.size() - 1; i++)
			(*v)[j++] = b[i] - b[i+1];
		random_shuffle(v->begin(), v->end());
	}

	vector<vec> p(n);
	for (int i = 0; i < n; i++) { p[i].x = x[i]; p[i].y = y[i]; }
	sort(p.begin(), p.end(), [] (const vec & a, const vec & b) { 
			if (a.halfplane() != b.halfplane()) return a.halfplane();
			return b.leftOf(vec({0,0}),a);
	});
	for (int i = n-1; i > 0; i--) p[i] = p[i-1];
	p[0].x = rand(-lim/10,lim/10); p[0].y = rand(-lim/10,lim/10);
	for (int i = 1; i < n; i++) { p[i] = p[i] + p[i-1]; }

	cout << n << endl;
	for (int i = 0; i < n; i++)
		cout << p[i].x << " " << p[i].y << endl;

	// generate m points outside of polygon p
	cout << m << endl;
	for (int i = 0; i < m; i++) {
		vec v; v.x = rand(-lim/10,lim/10); v.y = rand(-lim/10,lim/10);
		if (v.leftOf(p[0],p[1],true) && !v.leftOf(p[0],p[n-1],false)) {
			int lo = 2, hi = n-1; // first diagonal to the left of v
			while (lo < hi) {
				int md = (lo+hi)/2;
				if (v.leftOf(p[0],p[md],true)) lo = md+1;
				else hi = md;
			}
			if (v.leftOf(p[lo-1],p[lo],true) || (p[0].x == v.x && p[0].y == v.y)) { // is inside the polygon
				i--;
			} else {
				cout << v.x << " " << v.y << endl;
			}
		} else {
			cout << v.x << " " << v.y << endl;
		}
	}
}
