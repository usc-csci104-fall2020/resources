#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>


// Models a rational number represented as a numerator and denominator.
class Rational {
public:
    // Default constructor initializing the rational number to 0/1.
    Rational();

    // Initializes the rational number using n as the numerator and d as the
    // denominator. Stores the rational number in reduced form:
    //
    // Rational(2,-4) should yield a rational number of -1/2
    Rational(int n, int d);

    // ostream insertion operator: '<<'
    //
    // When outputting a Rational simply print the numerator (with the sign),
    // a '/' character, and the denominator. Thus, if the ostream operator is
    // applied to Rational(2, -4), "-1/2" should be output. If the ostream
    // operator is applied to Rational(-6, -4), "3/2" should be output.
    friend std::ostream& operator<<(std::ostream& out, const Rational& r);

    // istream extraction operator: '>>'
    //
    // When inputting a Rational, read a numerator, a '/', and a denominator
    // and set the Rational input reference with the appropriate value
    // specified by the values read.
    //
    // Any amount of whitespace may separate numerator, '/', and denominator.
    // The numerator and/or denominator may be negative when read.
    friend std::istream& operator>>(std::istream& in, Rational& r);

    // Add additional function prototypes here. You can discern what additional
    // prototypes are needed by studying rational_test.cpp and figuring out
    // what function call is needed for each rational operation. Use that
    // exercise as a checklist for the prototypes that need to be added here
    // and implemented. Only use the friend keyword if it's necessary. Some
    // examples are provided.

    // Add a rational number to another one, returning a new Rational.
    Rational operator+(const Rational& rhs) const;

    // Addition assignment returns a reference to this (*this) and is not const
    // because it modifies this.
    Rational& operator+=(const Rational& rhs);

    // We can use a similar pattern for operations with integers.
    Rational operator*(int rhs) const;

    // If you need to write an operator where the non-rational is on the left
    // side, you need to override the global multiplication operator. Since
    // that function will need to reference private members on rhs, which is
    // a Rational, we have to declare it as a friend in the Rational
    // declaration.
    friend Rational operator*(int lhs, const Rational& rhs);

    // Comparison operators are fairly straightforward. Note that you can
    // invoke another operator in your operator definition, just make sure you
    // don't end up creating an infinite recursive loop.
    bool operator==(const Rational& other) const;

    // TODO: prototype the rest of the operators you'll need

private:
    // Private helper functions that you must implement

    // Divides the numerator and denominator by their mutual gcd, leaving it
    // in reduced form.
    void reduce();

    // If the numerator is 0, sets the denominator to 1 to provide a standard
    // representation for 0.
    void normalize();

    // Private data members
    int n;
    int d;
};

// You may also add additional functions prototypes here if necessary.

#endif
