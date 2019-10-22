/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() { root = nullptr; }

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    if (find(word) == true) {
        return false;
    }

    if (root == nullptr) {
        TierNode* newRoot = new TierNode(word.at(0));
        newRoot->left = nullptr;
        newRoot->median = nullptr;
        newRoot->right = nullptr;
        root = newRoot;
        cout << root->singleChar << "999";
    }
    TierNode* curr = root;
    TierNode* prev = root;
    int i = 0;
    while (i < word.length() && curr != nullptr) {
        if (word.at(i) == curr->singleChar) {
            prev = curr;
            curr = curr->median;
            i++;
        } else if (word.at(i) < curr->singleChar) {
            curr = curr->left;
        } else if (word.at(i) > curr->singleChar) {
            curr = curr->right;
        }
        if (i == word.length()) {
            prev->frequency = freq;
            return true;
        }
    }
    int k = i;
    while (k < word.length()) {
        curr = new TierNode(word.at(k));
        curr->right = nullptr;
        curr->median = nullptr;
        curr->left = nullptr;
        prev = curr;
        curr = curr->median;
        k++;
        if (k == word.length()) {
            prev->frequency = freq;
            cout << prev->singleChar;
            return true;
        }
    }
}

/*
 */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) {
        return false;
    }
    TierNode* curr = root;
    TierNode* prev = root;
    int i = 0;
    while (i < word.length() && curr != nullptr) {
        if (word.at(i) == curr->singleChar) {
            cout << curr->singleChar << "123";
            prev = curr;
            curr = curr->median;
            i = i + 1;
        } else if (word.at(i) < curr->singleChar) {
            curr = curr->left;
        } else if (word.at(i) > curr->singleChar) {
            curr = curr->right;
        }
        if (i == word.length() && prev->frequency != 0) {
            return true;
        }
    }

    return false;
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* delete recursively
 */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }
void DictionaryTrie::deleteAll(TierNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        deleteAll(node->left);
    }
    if (node->median != nullptr) {
        deleteAll(node->median);
    }
    if (node->right != nullptr) {
        deleteAll(node->right);
    }
    delete node;
}