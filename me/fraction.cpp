#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Fraction {
private:
    T num;
    T den;

    T gcd(T a, T b) {
        while (b != 0) {
            T temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    Fraction(T num, T denom) : num(num), den(denom) {
        if (den == 0) {
            std::cerr << "Error: Den cannot be zero." << std::endl;
            exit(1);
        }
        simplify();
    }

    void simplify() {
        T divisor = gcd(num, den);
        num /= divisor;
        den /= divisor;
    }

    Fraction operator+(const Fraction& other) const {
        T newNum = num * other.den + other.num * den;
        T newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator-(const Fraction& other) const {
        T newNum = num * other.den - other.num * den;
        T newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator*(const Fraction& other) const {
        T newNum = num * other.num;
        T newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.num == 0) {
            std::cerr << "Error: Division by zero." << std::endl;
            exit(1);
        }
        T newNum = num * other.den;
        T newDen = den * other.num;
        return Fraction(newNum, newDen);
    }

    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }

    bool operator<=(const Fraction& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Fraction& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    void display() const {
        std::cout << num << "/" << den;
    }
};

// #include <iostream>

// template<typename T>
// class Fraction {
// private:
//     T numerator;
//     T denominator;

//     T gcd(T a, T b) {
//         while (b != 0) {
//             T temp = b;
//             b = a % b;
//             a = temp;
//         }
//         return a;
//     }

// public:
//     Fraction(T num, T denom) : numerator(num), denominator(denom) {
//         if (denominator == 0) {
//             std::cerr << "Error: Denominator cannot be zero." << std::endl;
//             exit(1);
//         }
//         simplify();
//     }

//     void simplify() {
//         T divisor = gcd(numerator, denominator);
//         numerator /= divisor;
//         denominator /= divisor;
//     }

//     Fraction operator+(const Fraction& other) const {
//         T newNumerator = numerator * other.denominator + other.numerator * denominator;
//         T newDenominator = denominator * other.denominator;
//         return Fraction(newNumerator, newDenominator);
//     }

//     Fraction operator-(const Fraction& other) const {
//         T newNumerator = numerator * other.denominator - other.numerator * denominator;
//         T newDenominator = denominator * other.denominator;
//         return Fraction(newNumerator, newDenominator);
//     }

//     Fraction operator*(const Fraction& other) const {
//         T newNumerator = numerator * other.numerator;
//         T newDenominator = denominator * other.denominator;
//         return Fraction(newNumerator, newDenominator);
//     }

//     Fraction operator/(const Fraction& other) const {
//         if (other.numerator == 0) {
//             std::cerr << "Error: Division by zero." << std::endl;
//             exit(1);
//         }
//         T newNumerator = numerator * other.denominator;
//         T newDenominator = denominator * other.numerator;
//         return Fraction(newNumerator, newDenominator);
//     }

//     void display() const {
//         std::cout << numerator << "/" << denominator;
//     }
// };

int main() {
    Fraction<int> frac1(1, 2);
    Fraction<int> frac2(3, 4);

    frac1.display();
    frac2.display();
    Fraction<int> sum = frac1 + frac2;
    Fraction<int> difference = frac1 - frac2;
    Fraction<int> product = frac1 * frac2;
    Fraction<int> quotient = frac1 / frac2;

    std::cout << "Sum: ";
    sum.display();
    std::cout << std::endl;

    std::cout << "Difference: ";
    difference.display();
    std::cout << std::endl;

    std::cout << "Product: ";
    product.display();
    std::cout << std::endl;

    std::cout << "Quotient: ";
    quotient.display();
    std::cout << std::endl;

    return 0;
}
