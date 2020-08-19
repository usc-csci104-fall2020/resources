#include "rational.h"
#include <iostream>
#include <sstream>

using namespace std;


// Your implementation of the Rational class must provide appropriate
// member and non-member functions such that the following program
// compiles and produces the correct output.
int main() {
    cout << "Constructor and insertion and extraction operators:" << endl;
    Rational r1;
    cout << r1 << endl;
    Rational r2(4, -20);
    cout << r2 << endl;
    Rational r3, r4, r5;
    int x = 2;
    std::stringstream ss("18 /-10 -14 / -6 2/4");
    ss >> r3 >> r4 >> r5;
    // Should yield 3 Rationals: r3=-9/5, r4=7/3, and r5=1/2
    cout << r3 << " " << r4 << " " << r5 << endl;

    cout << "Addition checks: " << endl;
    cout << (r2 + r3) << endl;
    cout << (x + r3) << endl;
    cout << (r3 + x) << endl;
    cout << "Multiplication checks: " << endl;
    cout << (r3 * r4) << endl;
    cout << (6 * r4) << endl;
    cout << (r4 * 6) << endl;
    cout << "Exponentiation checks: " << endl;
    cout << (r5 ^ 3) << endl;
    cout << (r5 ^ -2) << endl;
    cout << (r3 ^ 0) << endl;

    Rational req1(2, 4), req2(4, 8), rne3(-4, 8);
    cout << "Equal checks: " << endl;
    cout << (req1 == req2) << endl;
    cout << (req1 == rne3) << endl;
    cout << "Not Equal checks: " << endl;
    cout << (req1 != req2) << endl;
    cout << (req1 != rne3) << endl;
    cout << "Less-than checks: " << endl;
    cout << (r3 < r4) << endl;
    cout << (req1 < req2) << endl;
    cout << (rne3 < req1) << endl;

    Rational r5c1 = r5, r5c2 = r5, r5c3 = r5, r5c4 = r5;
    cout << "Assignment checks: " << endl;
    cout << (r5c1 += rne3) << endl;
    cout << (r5c2 += 5) << endl;
    cout << (r5c3 *= r2) << endl;
    cout << (r5c4 *= 3) << endl;

    Rational r6a(2, 4), r6b(-4, 8);
    cout << "Normalized 0 check: " << endl;
    cout << r6a + r6b << endl;

    return 0;
}
