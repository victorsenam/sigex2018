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
 * O(nm)
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
};

int main () {
	int n;
	cin >> n;
	vector<vec> p(n);
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		vec v;
		cin >> v.x >> v.y;
		double dist = 1./0.;
		for (int j = 0; j < n-1; j++)
			dist = min(dist, v.dist_seg(p[j],p[j+1]));
		cout << setprecision(20) << dist << endl;
	}
}
