//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "consts.h"
#include "counter.h"
#include "symbol_code.h"
#include "encoded_bytes.h"

struct huffman_tree {
    struct node {
        node();
        node(byte symbol, ull cnt);
        node(ull cnt, node *l, node *r);

        ull cnt;
        byte symbol;
        bool leaf;

        node *l, *r;

    };

    struct comparator {
        bool operator()(node *a, node *b) {
            return a->cnt < b->cnt;
        }
    };

    explicit huffman_tree(encoded_bytes &encoded_tree);
    explicit huffman_tree(counter counter);
    explicit huffman_tree(std::map<byte, ull> alphabet);

    ~huffman_tree();

    symbol_code get_code(byte x);
    node *root;

private:
    std::vector<symbol_code> code;

    void build(std::multiset<node *, comparator> dict);
    void dfs(node *v, symbol_code code);
    size_t dfs_decoder_helper(node *v, symbol_code code, encoded_bytes &encoded_tree, size_t cur);
    size_t dfs_decoder(node *v, size_t cur, encoded_bytes &encoded_tree);
    void del(node *&cur);
};

typedef huffman_tree::node node;

#endif //HUFFMAN_TREE_H
