#include <bits/stdc++.h>
using namespace std;

// Complex number structure
struct Complex {
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
            real * other.imag + imag * other.real);
    }
};

// Calculate root of unity
Complex rootOfUnity(int n) {
    return Complex(cos(2 * M_PI / n), sin(2 * M_PI / n));
}

// Cooley-Tukey FFT algorithm
void fft(vector<Complex>& A, int n, int dir) {
    if (n == 1) return;

    // Split into odd and even elements
    vector<Complex> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        even[i] = A[2 * i];
        odd[i] = A[2 * i + 1];
    }

    // Recursively compute FFT on halves
    fft(even, n / 2, dir);
    fft(odd, n / 2, dir);

    // Butterfly calculations
    Complex wn = rootOfUnity(n), w = 1;
    for (int i = 0; i < n / 2; ++i) {
        Complex u = even[i], v = odd[i] * w;
        A[i] = u + v;
        A[i + n / 2] = u - v;
        w = w * wn;
    }

    // Reverse direction for inverse FFT
    if (dir == -1) {
        for (int i = 0; i < n; ++i) {
            //A[i] = A[i] / Complex(n, 0);
            A[i].real /= n;
            A[i].imag /= n;
        }
    }
}

// Polynomial multiplication using FFT
vector<Complex> multiplyPolynomials(const vector<Complex>& a,
    const vector<Complex>& b) {
    int n = a.size();
    while (n < b.size()) n *= 2;
    while (n < 2 * a.size()) n *= 2;

    // Pad coefficients with zeros
    vector<Complex> A(n, 0), B(n, 0);
    for (int i = 0; i < a.size(); ++i) A[i] = a[i];
    for (int i = 0; i < b.size(); ++i) B[i] = b[i];

    // Perform FFT on both polynomials
    fft(A, n, 1);
    fft(B, n, 1);

    // Pointwise multiplication in frequency domain
    for (int i = 0; i < n; ++i) {
        A[i] = A[i] * B[i];
    }

    // Inverse FFT to get polynomial product
    fft(A, n, -1);

    // Extract coefficients and return result
    vector<Complex> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = A[i].real;
    }
    return result;
}


////////////////////////////

#include<bits/stdc++.h>
using namespace std;

typedef complex<double> cd;
// Function to perform Fast Fourier Transform (FFT)
vector<cd> fft(const vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1)
        return vector<cd>(1, a[0]);

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    vector<cd> y0 = fft(a0, invert);
    vector<cd> y1 = fft(a1, invert);

    double ang = 2 * M_PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int k = 0; k < n / 2; ++k) {
        a[k] = y0[k] + w * y1[k];
        a[k + n / 2] = y0[k] - w * y1[k];
        if (invert) {
            a[k] /= cd(2);
            a[k + n / 2] /= cd(2);
        }
        w *= wn;
    }
    return a;
}

// Function to multiply two polynomials using FFT
vector<double> multiply_polynomials(const vector<double>& a, const vector<double>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    fa = fft(fa, false);
    fb = fft(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fa = fft(fa, true);

    vector<double> result(n);
    for (int i = 0; i < n; ++i) result[i] = fa[i].real();
    return result;
}

int main() {
    vector<double> poly1 = { 1, 2, 3 }; // Coefficients of first polynomial
    vector<double> poly2 = { 3, 2, 1 }; // Coefficients of second polynomial

    vector<double> result = multiply_polynomials(poly1, poly2);

    cout << "Result of multiplication: ";
    for (double coeff : result) {
        cout << coeff << " ";
    }
    cout << endl;

    return 0;
}