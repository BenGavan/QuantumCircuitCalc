#include "complex.h"

double Complex::modulus() const {
    return std::sqrt(real * real + imaginary * imaginary);
}

Complex Complex::conjugate() const {
    return Complex{real, -imaginary};
}

double Complex::argument() const {
    return std::atan2(imaginary, real);
}

Complex Complex::operator+(const Complex &z) const {
    const Complex sum{real + z.real, imaginary + z.imaginary};
    return sum;
}

Complex Complex::operator-(const Complex &z) const {
    return {real - z.real, imaginary - z.imaginary};
}

Complex Complex::operator*(const Complex &z) const {
    return {real * z.real - imaginary * z.imaginary,
            imaginary * z.real + real * z.imaginary};
}

Complex Complex::operator/(const Complex &z) const {
    const double mod2 = z.real*z.real + z.imaginary*z.imaginary;
    return {(real * z.real + imaginary * z.imaginary) / mod2,
            (imaginary * z.real - real * z.imaginary) / mod2};
}

std::ostream &operator<<(std::ostream &os, const Complex &z) {
    // prints in format: "a+ib" or "a-ib"
    os << z.real;
    if (z.imaginary >= 0) {
        os << "+i";
    } else {
        os << "-i";
    }
    os << std::abs(z.imaginary);
    return os;
}

std::istream &operator>>(std::istream &is, Complex &z) {
    // input format: "a+ib" or "a-ib"
    char sign;

    is >> z.real >> sign;
    is.ignore(1);  // ignore 'i'
    is.putback(sign); // put the sign back in front of the imaginary component.
    is >> z.imaginary;

    return is;
}
