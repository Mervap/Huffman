//
// Created by Valery on 02.06.2018.
//

#include "huffman_tree.h"


huffman_tree::huffman_tree(encoded_bytes &encoded_tree) : root(new node()), code(MAX_DATA) {
    dfs_decoder(root, 0, encoded_tree);
}

huffman_tree::huffman_tree(counter counter) : huffman_tree(counter.get_not_zero()) {}

huffman_tree::huffman_tree(std::map<byte, ull> alphabet) : code(MAX_DATA) {
    std::multiset<node *, comparator> nodes;
    for (auto v: alphabet) {
        nodes.insert(new node(v.first, v.second));
    }
    build(nodes);
}

void huffman_tree::build(std::multiset<node *, comparator> nodes) {
    nodes.begin();
    while (nodes.size() > 1) {
        node *l = *nodes.begin();
        nodes.erase(nodes.begin());
        node *r = *nodes.begin();
        nodes.erase(nodes.begin());
        nodes.insert(new node(l->cnt + r->cnt, l, r));
    }

    if (nodes.size() == 1) {
        if ((*nodes.begin())->leaf) {
            root = new node();
            root->l = *nodes.begin();
        } else {
            root = *nodes.begin();
        }
        dfs(root, symbol_code());
    } else {
        root = nullptr;
    }
}

void huffman_tree::dfs(node *v, symbol_code symbolCode) {
    if (v == nullptr) {
        return;
    }

    if (v->leaf) {
        code[v->symbol] = symbolCode;
    }
    symbolCode.push_back(0);
    dfs(v->l, symbolCode);
    symbolCode.pop_back();

    symbolCode.push_back(1);
    dfs(v->r, symbolCode);
}


size_t huffman_tree::dfs_decoder(node *v, size_t cur, encoded_bytes &encoded_tree) {
    if (encoded_tree.empty()) {
        return 0;
    }

    if (encoded_tree[cur] == 1) {
        v->leaf = true;
        return cur + 1;
    }

    v->l = new node();
    cur = dfs_decoder(v->l, cur + 1, encoded_tree);

    if (encoded_tree[cur] == 0) {
        v->r = new node();
        cur = dfs_decoder(v->r, cur + 1, encoded_tree);
    }

    if (v == root) {
        dfs_decoder_helper(v, symbol_code(), encoded_tree, cur + 1);
    }

    return cur + 1;
}

size_t huffman_tree::dfs_decoder_helper(node *v, symbol_code symbolCode, encoded_bytes &encoded_tree, size_t cur) {
    if (v == nullptr) {
        return cur;
    }

    if (v->leaf) {
        byte x = 0;
        for (size_t i = 0; i < BYTE_SIZE; ++i) {
            x <<= 1;
            x |= encoded_tree[cur + i];
        }
        cur += BYTE_SIZE;
        v->symbol = x;
        code[x] = symbolCode;
    }
    symbolCode.push_back(0);
    cur = dfs_decoder_helper(v->l, symbolCode, encoded_tree, cur);
    symbolCode.pop_back();

    symbolCode.push_back(1);
    cur = dfs_decoder_helper(v->r, symbolCode, encoded_tree, cur);

    return cur;
}

huffman_tree::~huffman_tree() {
    del(root);
}

void huffman_tree::del(node *&v) {
    if (v != nullptr) {
        del(v->l);
        del(v->r);

        delete v;
        v = nullptr;
    }
}

symbol_code huffman_tree::get_code(byte x) {
    return code[x];
}

huffman_tree::node::node() : cnt(0), symbol(0), leaf(false), l(nullptr), r(nullptr) {}

huffman_tree::node::node(byte symbol, ull cnt) : cnt(cnt), symbol(symbol), leaf(true), l(nullptr), r(nullptr) {}

huffman_tree::node::node(ull cnt, node *l, node *r) : cnt(cnt), symbol(0), leaf(false), l(l), r(r) {}
