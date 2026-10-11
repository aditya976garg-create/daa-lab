#include <iostream>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const {
        return a->freq > b->freq;
    }
};

Node* buildTree(const string& text) {
    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (const auto& p : freq) pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* a = pq.top();
        pq.pop();
        Node* b = pq.top();
        pq.pop();
        pq.push(new Node('\0', a->freq + b->freq, a, b));
    }
    return pq.top();
}

void buildCodes(Node* root, const string& path, map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = path.empty() ? "0" : path;
        return;
    }
    buildCodes(root->left, path + "0", codes);
    buildCodes(root->right, path + "1", codes);
}

string encode(const string& text, const map<char, string>& codes) {
    string result;
    for (char c : text) result += codes.at(c);
    return result;
}

string decode(const string& bits, Node* root) {
    string result;
    if (!root->left && !root->right) {
        for (size_t i = 0; i < bits.size(); i++) result += root->ch;
        return result;
    }
    Node* cur = root;
    for (char b : bits) {
        cur = (b == '0') ? cur->left : cur->right;
        if (!cur->left && !cur->right) {
            result += cur->ch;
            cur = root;
        }
    }
    return result;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    string text;
    getline(cin, text);
    if (text.empty()) return 0;

    Node* root = buildTree(text);

    map<char, string> codes;
    buildCodes(root, "", codes);

    cout << "Huffman Codes:\n";
    for (const auto& p : codes) {
        cout << "'" << p.first << "' : " << p.second << "\n";
    }

    string encoded = encode(text, codes);
    string decoded = decode(encoded, root);

    cout << "\nEncoded: " << encoded << "\n";
    cout << "Decoded: " << decoded << "\n";

    size_t originalBits = text.size() * 8;
    size_t compressedBits = encoded.size();
    cout << "\nOriginal size:   " << originalBits << " bits\n";
    cout << "Compressed size: " << compressedBits << " bits\n";
    cout << "Compression:     "
         << (100.0 * (originalBits - compressedBits) / originalBits) << "%\n";

    freeTree(root);
    return 0;
}
