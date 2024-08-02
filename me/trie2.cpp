#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    unordered_map<string, TrieNode*> children;
    bool isEndOfPath;
    TrieNode() : isEndOfPath(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& path) {
        string currentPath = "";
        TrieNode* currentNode = root;
        for (const string& token : split(path, '/')) {
            if (currentNode->children.count(token) == 0) {
                currentNode->children[token] = new TrieNode();
            }
            currentNode = currentNode->children[token];
            currentPath += "/" + token;
        }
        currentNode->isEndOfPath = true;
    }

    bool search(const string& path) {
        string currentPath = "";
        TrieNode* currentNode = root;
        for (const string& token : split(path, '/')) {
            if (currentNode->children.count(token) == 0) {
                return false;
            }
            currentNode = currentNode->children[token];
            currentPath += "/" + token;
        }
        return currentNode->isEndOfPath;
    }

private:
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        size_t start = 0, end = 0;
        while ((end = str.find(delimiter, start)) != string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    ~Trie() {
        delete root;
    }
};
