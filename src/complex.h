#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>
#include<cmath>
#include<sstream>

class Complex {
    friend std::ostream &operator<<(std::ostream &os, const Complex &z);
    friend std::istream &operator>>(std::istream &is, Complex &z);
private:
    double real, imaginary;
public:
    Complex() : real{0}, imaginary{0} {}
    Complex(const double real_in, const double imaginary_in) :
        real{real_in}, imaginary{imaginary_in} {}

    ~Complex() {}

    double get_real() const { return real; }
    double get_imaginary() const { return imaginary; }

    double modulus() const;
    double argument() const;
    Complex conjugate() const;

    Complex operator+(const Complex &z) const;
    Complex operator-(const Complex &z) const;
    Complex operator*(const Complex &z) const;
    Complex operator/(const Complex &z) const;
};

#endif // COMPLEX_H