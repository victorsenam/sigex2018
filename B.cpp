#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

/* Calculates the distance between each point on a stream of points and a 
 * single given convex polygon.
 *
 * It receives, from the standart input, an integer n, the 
 * size of the polygon, it's vertices in counter-clockwise
 * order, an integer m, the size of the stream of points
 * and the m points contained in this stream.
 *
 * It outputs, for each i from 1 to m, the euclidean
 * distance between v[i] and the polygon p.
 *
 * Input:
 * n
 * p[1].x p[1].y
 * p[2].x p[2].y
 * ...
 * p[n].x p[n].y
 * m
 * v[1].x v[1].y
 * v[2].x v[2].y
 * ...
 * v[m].x v[m].y
 *
 * Output:
 * r[1]
 * r[2]
 * ...
 * r[m]
 *
 * Complexity:
 * O(n + mlog(n))
 */

struct vec {
	ll x, y;

	inline vec operator - (vec o) { return {x - o.x, y - o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y}; }
	inline ll operator ^ (vec o) { return x * o.y - y * o.x; }
	inline ll operator * (vec o) { return x * o.x + y * o.y; }
	inline ll cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a||(this)b|sen(angle)
	inline ll inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a||(this)b|cos(angle)
	inline int ccw (vec a, vec b) { ll o = cross(a,b); return (0 < o) - (o < 0); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { ll o = inner(a,b); return (0 < o) - (o < 0); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline double dist (vec o) { return sqrt(inner(o,o)); }
	
	double dist_lin (vec a, vec b) { return double(abs(cross(a,b)))/a.dist(b); }
	double dist_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist_lin(a,b) : min(dist(a),dist(b)); }

	bool operator < (vec o) const { return (x!=o.x)?x<o.x:y>o.y;}

	double dist_halfhull (vector<vec> & p, int lo, int hi) {
		hi--;
		cout << lo << " " << hi << " ";
		while (lo < hi) {
			int md = (lo+hi+1)/2;
			if (dir(p[lo],p[(lo+1)%p.size()]) >= 0) lo = md;
			else hi = md-1;
		}
		return dist_seg(p[lo],p[(lo+1)%p.size()]);
	}
};

void rotate (vector<vec> & p) {
	vector<vec> q = p;
	int mn = 0;
	for (int i = 1; i < p.size(); i++) if (q[i] < q[mn]) mn = i;
	for (int i = 0; i < p.size(); i++) p[i] = q[(mn+i)%p.size()];
}

int main () {
	int n;
	cin >> n;
	vector<vec> p(n);
	for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
	rotate(p);
	int mx = 0; for (int i = 1; i < n; i++) if (p[mx] < p[i]) mx = i;

	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		vec v;
		cin >> v.x >> v.y;

		if (v.ccw(p[0],p[mx]) <= 0) { // inferior hull
			cout << setprecision(20) << v.dist_halfhull(p,0,mx) << endl;
		} else { // superior hull
			cout << setprecision(20) << v.dist_halfhull(p,mx,n) << endl;
		}
	}
}
