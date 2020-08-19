#include "rational.h"
#include <stdexcept>
// Libraries may be included as necessary

using namespace std;


Rational::Rational() : n(0), d(1) {}

Rational::Rational(int n, int d) {
    // Since the denominator cannot be zero an exception is thrown
    if (d == 0) {
        throw std::invalid_argument("division by zero");
    }

    // TODO: continue your implementation below.
    // You should likely set the member variables ad then call this->reduce()
    // and this->normalize().
}

void Rational::normalize() {
    // In C++ you don't always have to use this-> to denote a member variable.
    // If you omit it, the compiler will infer that n and d are indeed members
    // of Rational. There are two reasons you will see or use this->:
    //
    // 1. If you have a local variable that has the same name as a member
    //    variable, you need to use this-> to differentiate the two. If you
    //    created `int n` on this next line, the compiler would decide that
    //    any consequent uses of that variable refer to the local n, not our
    //    member variable. To specifically access the member n in this
    //    scenario, we'd use this->n.
    //
    // 2. Style. Some people (like me, Noah, the guy writing this) prefer to
    //    to use this-> to make it clear what variables are members when
    //    reading through the code. Others use a prefix (m_, i.e. m_member) or
    //    a suffix (_, i.e. member_) to denote it. In assignments where you
    //    write your own classes, this will be up to you. For now, do as you
    //    wish, but don't forget readability :)
    //
    // And feel free to delete this huge comment.
    if (n == 0 && d != 1) {
        d = 1;
    }
}

Rational Rational::operator+(const Rational& rhs) const {
    // TODO
}

Rational& Rational::operator+=(const Rational& rhs) {
    // TODO
}

Rational Rational::operator*(int rhs) const {
    // TODO
}

// This operator isn't prefixed by Rational:: because it's not actually a
// member of Rational. It just tells the compiler what to do when it sees
// multiplication between an int on the left and a Rational on the right. Our
// friend declaration simply enabled us to access private members on the const
// Rational& rhs in the function body.
//
// Note that we could implement any of the other operators above this same way
// using the corresponding global operator and passing a const Rational& lhs as
// the first argument, it's just a matter of convenience.
Rational operator*(int lhs, const Rational& rhs) {
    // TODO
}

bool Rational::operator==(const Rational& other) const {
    // TODO
}

// TODO: implement the rest of your prototyped methods
