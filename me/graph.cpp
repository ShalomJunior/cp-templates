#include<bits/stdc++.h>
using namespace std;

template <typename T>
class KthCommonAncestor {
public:
    KthCommonAncestor(const std::vector<std::vector<T>>& adj_list) : adj_list_(adj_list) {
        computeAncestors();
    }

    T kthAncestor(T node, int k) const {
        for (int i = 0; i < log2(depth_ + 1); ++i) {
            if (k & (1 << i)) {
                node = ancestors_[i][node];
                if (node == -1) {
                    // No ancestor at this distance
                    return -1;
                }
            }
        }
        return node;
    }

private:
    std::vector<std::vector<T>> adj_list_;
    std::vector<int> depth_;  // Depth of each node
    std::vector<std::vector<T>> ancestors_;  // Precomputed 2^i-th ancestors
    int max_depth_ = 0;

    void computeAncestors() {
        int n = adj_list_.size();
        depth_.assign(n, -1);
        ancestors_.assign(log2(n) + 1, std::vector<T>(n, -1));

        // Depth-first search to compute depths and immediate parents
        std::function<void(T, T)> dfs = [&](T node, T parent) {
            depth_[node] = (parent == -1) ? 0 : depth_[parent] + 1;
            max_depth_ = std::max(max_depth_, depth_[node]);
            ancestors_[0][node] = parent;
            for (T child : adj_list_[node]) {
                if (child != parent) {
                    dfs(child, node);
                }
            }
            };
        dfs(0, -1);  // Start DFS from root (assuming node 0 is the root)

        // Precompute ancestors using binary lifting
        for (int i = 1; i < ancestors_.size(); ++i) {
            for (int node = 0; node < n; ++node) {
                if (ancestors_[i - 1][node] != -1) {
                    ancestors_[i][node] = ancestors_[i - 1][ancestors_[i - 1][node]];
                }
            }
        }
    }
};