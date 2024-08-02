#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct WaveletTree {
    int lo, hi;
    WaveletTree* left, * right;
    std::vector<T> left_vals, right_vals;

    WaveletTree(const std::vector<T>& arr, int low, int high) : lo(low), hi(high) {
        if (low == high) return;

        int mid = (low + high) / 2;
        T pivot = arr[mid];

        int l = 0, r = 0;
        for (int i = low; i <= high; i++) {
            if (arr[i] < pivot) {
                left_vals.push_back(arr[i]);
                l++;
            }
            else {
                right_vals.push_back(arr[i]);
                r++;
            }
        }

        std::vector<T> temp(arr.begin() + low, arr.begin() + low + l);
        left = new WaveletTree(temp, low, low + l - 1);
        temp = std::vector<T>(arr.begin() + low + l, arr.begin() + high + 1);
        right = new WaveletTree(temp, low + l, high);
    }

    // Count occurrences of x in the range [a, b]
    int rank(T x, int a, int b) {
        if (x < left_vals[0] || x > right_vals[0]) return 0;
        if (a <= lo && hi <= b) {
            return std::upper_bound(left_vals.begin(), left_vals.end(), x) - left_vals.begin();
        }
        int mid = (lo + hi) / 2;
        int left_count = 0;
        if (a <= mid) left_count = left->rank(x, a, b);
        if (b > mid) left_count += right->rank(x, a, b);
        return left_count;
    }

    // K-th smallest element in the range [a, b]
    T kth(int k, int a, int b) {
        if (a <= lo && hi <= b) {
            return k <= left_vals.size() ? left_vals[k - 1] : right_vals[k - left_vals.size() - 1];
        }
        int mid = (lo + hi) / 2;
        int left_size = left_vals.size();
        if (k <= left_size) return left->kth(k, a, std::min(b, mid));
        return right->kth(k - left_size, std::max(a, mid + 1), b);
    }
};
