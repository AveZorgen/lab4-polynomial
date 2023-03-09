#include <iostream>
#include <fstream>
#include "Polynomial.h"

using namespace std;

int main() {
    Polynomial ll1, ll2;
    ifstream file("source2.txt");
    file >> ll1 >> ll2;
    cout << ll1 << "\n" << ll2 << "\n";
    Polynomial ll3 = ll1 + ll2;
    cout << ll3 << "\n";
    ll3 = ll1 * ll2;
    cout << ll3 << "\n";
    cout << ll1.approx(1, 0, 0) << " " << ll1.approx(1, 1, 0) << " " << ll1.approx(2, 3, 17) << "\n";
    cout << ll2.approx(1, 0, 0) << " " << ll2.approx(1, 1, 0) << " " << ll2.approx(5, 1, 2) << "\n";
    return 0;
}
