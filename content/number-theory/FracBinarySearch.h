/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q \le N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac { ll p, q; };

template<class F>
Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
	if (f(lo)) return lo;
	assert(f(hi));
	while (A || B) {
		ll adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B; B = !!adv;
	}
	return dir ? hi : lo;
}

// Custom version
struct Frac {
	ll n, d;
	Frac(ll n_, ll d_, bool reduce = false) {
		n = n_, d = d_;
		if (reduce) {
			ll g = __gcd(n, d);
			n /= g, d /= g;
		}
	}
	Frac(ll n): n(n), d(1) {}
	Frac operator+(const Frac &f) const { return Frac(n*f.d + d*f.n, d*f.d, true); }
	Frac operator-(const Frac &f) const { return Frac(n*f.d - d*f.n, d*f.d, true); }
	Frac operator*(const Frac &f) const { return Frac(n*f.n, d*f.d, true); }
	Frac operator/(const Frac &f) const { return Frac(n*f.d, d*f.n, true); }
	Frac operator+(const ll x) const { return Frac(n+x*d, d); }
	Frac operator-(const ll x) const { return Frac(n-x*d, d); }
	Frac operator*(const ll x) const { return Frac(n*x, d, true); }
	Frac operator/(const ll x) const {
		if (n % d == 0) return Frac(n/d, d);
		return Frac(n, d*x, true);
	}
	bool operator<(const Frac &f) const { return n*f.d < f.n*d; }
	bool operator>(const Frac &f) const { return n*f.d > f.n*d; }
	bool operator==(const Frac &f) const { return n*f.d == f.n*d; }
	bool operator<(const ll x) const { return n < x*d; }
	bool operator>(const ll x) const { return n > x*d; }
};

// smallest is true if finding smallest possible x s.t. f(x) works, otherwise largest.
template<class F>
Frac fracBS(F f, ll N, bool smallest = true) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
	if (smallest) {
		if (f(lo)) return lo;
		assert(f(hi));
	} else {
		if (f(hi)) return hi;
		assert(f(lo));
	}
	while (A || B) {
		ll adv = 0, step = 1; // move hi if dir, else lo (for smallest)
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.n * adv + hi.n, lo.d * adv + hi.d};
			if (abs(mid.n) > N || mid.d > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.n += lo.n * adv;
		hi.d += lo.d * adv;
		dir = !dir;
		swap(lo, hi);
		A = B; B = !!adv;
	}
	return dir ? hi : lo;
}
