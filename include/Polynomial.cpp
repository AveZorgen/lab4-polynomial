#include <iostream>
#include <string>
#include <sstream>
#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial() {
	start = new Link(0);
	start->next = start;
	end = start;
}

Polynomial::Polynomial(const Polynomial& p) {
    start = new Link(0);
    start->next = start;
    end = start;
    Link* curr = p.start->next;
    while (curr != p.start) {
	    addl(curr->val);
	    curr = curr->next;
    }
}

Polynomial::~Polynomial() {
	clean();
	delete start;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this == &p) {
		return *this;
	}
	clean();
	Link* curr = p.start->next;
	while (curr != p.start) {
		addl(curr->val);
		curr = curr->next;
	}
	return *this;
}

void Polynomial::addasc(Monom val) {
	Link* tmp = start;
	while (tmp->next != start) {
		if (tmp->next->val > val) {
			Link* new_link = new Link(val, tmp->next);
			tmp->next = new_link;
			return;
		}
		if (tmp->next->val.deg_eq(val)) {
			Monom m = tmp->next->val + val;
			if (m.iszero()) {
				Link* next = tmp->next;
			    tmp->next = next->next;
				delete next;
			} else {
			    tmp->next->val = m;
			}
			return;
		}
		tmp = tmp->next;
	}
	Link* n = new Link(val, start);
	tmp->next = n;
}

void Polynomial::addl(Monom val) {
	Link* n = new Link(val, start);
	end->next = n;
	end = n;
}

void Polynomial::clean() {
	Link* tmp = start;
	Link* tmp2 = start->next;
	while (tmp2 != start) {
		tmp->next = tmp2->next;
		delete tmp2;
		tmp2 = tmp->next;
	}
	end = start;
}

//LList LList::intersect(const LList& p) {
//    LList lln;
//    Link* tmp = start->next;
//    Link* tmp2 = p.start->next;
//    while (tmp != start && tmp2 != p.start) {
//        if (tmp->val == tmp2->val) {
//            lln.addl(tmp->val);
//            tmp = tmp->next;
//            tmp2 = tmp2->next;
//        } else if (tmp->val < tmp2->val)
//            tmp = tmp->next;
//        else tmp2 = tmp2->next;
//    }
//    return lln;
//}

Polynomial Polynomial::operator +(const Polynomial& p) const {
	Polynomial lln;
	Link* tmp = start->next;
	Link* tmp2 = p.start->next;
	Monom m;
	while (tmp != start && tmp2 != p.start) {
		if (tmp->val.deg_eq(tmp2->val)) {
			m = tmp->val + tmp2->val;
			if (!m.iszero())
				lln.addl(m);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		else if (tmp->val < tmp2->val) {
			lln.addl(tmp->val);
			tmp = tmp->next;
		}
		else {
			lln.addl(tmp2->val);
			tmp2 = tmp2->next;
		}
	}
	while (tmp != start) { lln.addl(tmp->val); tmp = tmp->next; }
	while (tmp2 != p.start) { lln.addl(tmp2->val); tmp2 = tmp2->next; }
	return lln;
}

Polynomial Polynomial::operator *(const Polynomial& p) const {
	Polynomial lln;
	Link* tmp = start->next;
	Link* tmp2 = p.start->next;
	Monom m;
	while (tmp != start) {
		while (tmp2 != p.start) {
			m = tmp->val * tmp2->val;
			if (!m.iszero())
				lln.addasc(m);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		tmp2 = p.start->next;
	}
	return lln;
}

double Polynomial::approx(double _x, double _y, double _z) const {
	Link* tmp = start->next;
	double res = 0;
	while (tmp != start) {
		res += tmp->val.approx(_x, _y, _z);
		tmp = tmp->next;
	}
	return res;
}

bool Polynomial::operator==(const Polynomial& p) const {
	Link* tmp = start->next;
	Link* tmp2 = p.start->next;
	while (tmp != start && tmp2 != p.start) {
		if (!(tmp->val == tmp2->val)) return false;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if (tmp!= start || tmp2 != p.start) return false;
	return true;
}


istream& operator >>(istream& in, Polynomial& p) {
	string str;
	in >> str;
	string t;
	p.clean();
	str += " ";
	bool st = true;
	for (const char c : str) {
		if ((c == ' ') || (c == '+') || (c == '-')) {
			if (st) {
				t += c;
				st = false;
			}
			else if (!t.empty()) {
				istringstream ss(t);
				cout << " |" << t << "| ";
				Monom m;
				ss >> m;
				p.addasc(m);
				t = c;
			}
		}
		else {
			t += c;
			st = c == '^';
		}
	}
	cout << "\n";
	return in;
}

ostream& operator <<(ostream& out, const Polynomial& p) {
	Link* tmp = p.start->next;
	while (tmp != p.start) {
		out << tmp->val << " ";
		tmp = tmp->next;
	}
	out << " ";
	return out;
}