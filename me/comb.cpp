#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Combinatorics {
private:
    vector<T> factorial;
    vector<T> invFactorial;
    T mod;

public:
    // Constructor to initialize the combinatorics class with precomputed factorials and inverses
    Combinatorics(int maxSize, T modValue) : mod(modValue) {
        factorial.resize(maxSize + 1);
        invFactorial.resize(maxSize + 1);

        // Precompute factorials and modular inverses
        factorial[0] = invFactorial[0] = 1;
        for (int i = 1; i <= maxSize; ++i) {
            factorial[i] = (factorial[i - 1] * i) % mod;
            invFactorial[i] = modInverse(factorial[i], mod);
        }
    }

    // Function to calculate the modular inverse of a number
    T modInverse(T a, T m) {
        T m0 = m;
        T y = 0, x = 1;

        while (a > 1) {
            T q = a / m;
            T t = m;

            m = a % m;
            a = t;
            t = y;

            y = x - q * y;
            x = t;
        }

        // Make x positive
        if (x < 0)
            x += m0;

        return x;
    }

    // Function to calculate n choose r (nCr) using precomputed factorials and inverses
    T nCr(T n, T r) {
        assert(n >= r && r >= 0);

        if (n == r || r == 0)
            return 1;

        T result = (factorial[n] * invFactorial[r]) % mod;
        result = (result * invFactorial[n - r]) % mod;

        return result;
    }
};