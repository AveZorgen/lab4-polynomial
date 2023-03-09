#pragma once
#include <iostream>
#include <string>
const int P = 20;

using namespace std;

class Monom {
public:
	Monom(int _s = 0, double _c = 1) : s(_s), c(_c) {}
	Monom(int x, int y, int z, double _c = 1) : s(P* P* x + P * y + z), c(_c) {}
private:
	int s;
	double c;
	bool iszero() { return c == 0; }
	double approx(double _x, double _y, double _z) {
		int t = s;
		int zp = t % P; t /= P;
		int yp = t % P; t /= P;
		int xp = t % P;
		return c * pow(_x, xp - P / 2) * pow(_y, yp - P / 2) * pow(_z, zp - P / 2);
	}
	bool deg_eq(Monom& m) { return s == m.s; }
	bool operator ==(Monom& m) const { return s == m.s && c == m.c; }
	weak_ordering operator <=>(Monom& m) { return s <=> m.s; }
	Monom operator+(Monom& m) { return { s, c + m.c }; }
	Monom operator*(Monom& m) const { return {s + m.s - (P * P * P + P * P + P) / 2, c * m.c }; }
	friend ostream& operator <<(ostream& out, Monom& m) {
		int t = m.s, zp, yp, xp;
		t = (zp = t % P, t / P);
		t = (yp = t % P, t / P);
		t = (xp = t % P, t / P);
		out << "{" << m.c <<
			"| " << xp - P / 2 <<
			", " << yp - P / 2 <<
			", " << zp - P / 2 <<
			"| " << m.s <<
			"}";
		return out;
	}
	friend istream& operator >>(istream& in, Monom& m) {
		string str;
		in >> str;
		m.c = 1.0;
		m.s = (P * P * P + P * P + P) / 2;
		int st = 0;
		int p_st = 0;
		bool ch = false;
		string t;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '^') {
				t = "";
				continue;
			}
			else if (str[i] == 'x') {
				ch = true;
				p_st = st;
				st = 3;
			}
			else if (str[i] == 'y') {
				ch = true;
				p_st = st;
				st = 2;
			}
			else if (str[i] == 'z') {
				ch = true;
				p_st = st;
				st = 1;
			}
			if (!ch) {
				t += str[i];
			}
			else {
				if (p_st == 0) {
					if (!t.empty()) {
						m.c = stod(t);
					}
				}
				if (p_st > 0) {
					if (t.empty()) t = "1";
					int pp = pow(P, p_st - 1);
					m.s += stoi(t) * pp;
				}
				t = "";
				ch = false;
			}
		}
		if (st == 0) {
			if (!t.empty()) {
				m.c = stod(t);
			}
		}
		if (st > 0) {
			if (t.empty()) t = "1";
			int pp = pow(P, st - 1);
			m.s += stoi(t) * pp;
		}
		return in;
	}
	friend class Polynomial;
};

struct Link
{
	Monom val;
	Link* next;
	Link(Monom _v, Link* _n = nullptr) : val(_v), next(_n) {}
};

class Polynomial {
	Link* start;
	Link* end;
	void addl(Monom val);
public:
	Polynomial();
	Polynomial(const Polynomial& p);
	~Polynomial();
	Polynomial& operator =(const Polynomial& p);
	friend ostream& operator <<(ostream& out, const Polynomial& p);
	friend istream& operator >>(istream& in, Polynomial& p);
	void addasc(Monom val);
	void clean();
	//LList intersect(const LList& p);
	Polynomial operator +(const Polynomial& p) const;
	Polynomial operator *(const Polynomial& p) const;
	bool operator==(const Polynomial&) const;
	double approx(double _x, double _y, double _z) const;
};