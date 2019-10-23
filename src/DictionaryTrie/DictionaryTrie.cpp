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
    // first check if the word is already in the tree or not
    if (find(word) == true) {
        return false;
    }
    // check the tree is empty or not
    if (root == nullptr) {
        root = new TierNode(word.at(0));
        root->left = nullptr;
        root->median = nullptr;
        root->right = nullptr;
    }
    TierNode* curr = root;
    TierNode* prev = root;
    int i = 0;
    // search if every character of word is in the tree or not
    // if in the tree, then change the frequency
    // if not in the tree, return the address of the next node to create
    // new Node
    while (i < word.length() && curr != nullptr) {
        if (word.at(i) == curr->singleChar) {
            prev = curr;
            curr = curr->median;
            //   prev->median = curr;
            i++;
        } else if (word.at(i) < curr->singleChar) {
            prev = curr;
            // prev->left = curr;
            curr = curr->left;
            //   prev->left = curr;
        } else if (word.at(i) > curr->singleChar) {
            prev = curr;
            // prev->right = curr;
            curr = curr->right;
            //   prev->right = curr;
        }
        if (i == word.length()) {
            prev->frequency = freq;
            return true;
        }
    }
    // create new node for the remaining characters
    curr = new TierNode(word.at(i));
    curr->right = nullptr;
    curr->median = nullptr;
    curr->left = nullptr;
    if (word.at(i) < prev->singleChar) {
        prev->left = curr;
        prev = curr;
        curr = curr->median;
        i++;
    } else if (word.at(i) > prev->singleChar) {
        prev->right = curr;
        prev = curr;
        curr = curr->median;
        i++;
    } else if (word.at(i) == prev->singleChar) {
        prev->median = curr;
        prev = curr;
        curr = curr->median;
        i++;
        int k = i;
        while (k < word.length()) {
            curr = new TierNode(word.at(k));
            cout << curr->singleChar << "135";
            cout << prev->singleChar << "120";
            curr->right = nullptr;
            curr->median = nullptr;
            curr->left = nullptr;
            prev->median = curr;
            prev = curr;
            curr = curr->median;
            k++;
        }
        i = k;
    }
    if (i == word.length()) {
        prev->frequency = freq;
        cout << prev->singleChar << "456";
        return true;
    }
    if (root->right != nullptr) {
        cout << root->right->singleChar << "328";
    }
    //   int k = i;
    //  while (k < word.length()) {
    //    curr = new TierNode(word.at(k));
    //  cout << curr->singleChar << "135";
    // cout << prev->singleChar << "120";
    //  curr->right = nullptr;
    //  curr->median = nullptr;
    //  curr->left = nullptr;
    //  prev->median = curr;
    //  prev = curr;
    //  curr = curr->median;
    //  k++;
    //  if (root->right != nullptr) {
    //     cout << root->right->singleChar << "648";
    // }
    //  if (k == word.length()) {
    //    prev->frequency = freq;
    //   cout << prev->singleChar << "456";
    //    return true;
    //  }
    // }
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

    // searching for the each character along the tree
    // if in the tree and the freq is not 0  we find the word
    // else we did not find that word.
    while (i < word.length() && curr != nullptr) {
        if (word.at(i) == curr->singleChar) {
            cout << curr->singleChar << "123";
            prev = curr;
            curr = curr->median;
            i = i + 1;
        } else if (word.at(i) < curr->singleChar) {
            prev = curr;
            curr = curr->left;
        } else if (word.at(i) > curr->singleChar) {
            prev = curr;
            curr = curr->right;
        }
    }
    if (i == word.length() && prev->frequency != 0) {
        return true;
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