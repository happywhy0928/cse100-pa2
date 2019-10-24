/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
bool sortByFrequency(const pair<string, unsigned int>& x,
                     const pair<string, unsigned int>& y) {
    if (x.second == y.second) {
        return x.first < y.first;
    } else
        return x.second > y.second;
}

/* TODO */
DictionaryTrie::DictionaryTrie() { root = nullptr; }
DictionaryTrie::TierNode::TierNode(char charter) {
    frequency = 0;
    singleChar = charter;
    left = nullptr;
    median = nullptr;
    right = nullptr;
}
/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    if (find(word) == true) {
        return false;
    }
    int count = 0;
    char currLetter = word[count];
    TierNode* curr = root;
    TierNode* inputNode = new TierNode(currLetter);
    for (;;) {
        currLetter = word[count];
        inputNode->singleChar = currLetter;
        if (root == nullptr) {
            root = inputNode;
            count = count + 1;
            while (count < word.size()) {
                currLetter = word[count];
                inputNode->median = new TierNode(currLetter);
                inputNode = inputNode->median;
                count++;
            }
            inputNode->frequency = freq;
            return true;
        } else if (inputNode->singleChar < curr->singleChar) {
            if (curr->left != nullptr) {
                curr = curr->left;
            } else {
                curr->left = inputNode;
                curr = curr->left;
                count = count + 1;
                while (count < word.size()) {
                    currLetter = word[count];
                    curr->median = new TierNode(currLetter);
                    curr = curr->median;
                    count++;
                }
                curr->frequency = freq;
                return true;
            }
        } else if (inputNode->singleChar > curr->singleChar) {
            if (curr->right != nullptr) {
                curr = curr->right;
            } else {
                curr->right = inputNode;
                curr = curr->right;
                count++;
                while (count < word.size()) {
                    currLetter = word[count];
                    curr->median = new TierNode(currLetter);
                    curr = curr->median;
                    count++;
                }
                curr->frequency = freq;
                return true;
            }
        } else {
            if (count == word.size() - 1) {
                curr->frequency = freq;
                return true;
            } else {
                if (curr->median != nullptr) {
                    curr = curr->median;
                    count++;
                } else {
                    count++;
                    currLetter = word[count];
                    inputNode->singleChar = currLetter;
                    curr->median = inputNode;
                    curr = curr->median;
                    count++;
                    while (count < word.size()) {
                        currLetter = word[count];
                        curr = new TierNode(currLetter);
                        curr = curr->median;
                        count++;
                    }
                    curr->frequency = freq;
                    return true;
                }
            }
        }
    }
}
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) {
        return false;
    }
    TierNode* node = root;
    int i = 0;
    for (;;) {
        if (word[i] < node->singleChar) {
            if (node->left) {
                node = node->left;
            } else {
                return false;
            }
        } else if (word[i] > node->singleChar) {
            if (node->right) {
                node = node->right;
            } else {
                return false;
            }
        } else {
            if (i == word.size() - 1 && node->frequency != 0) {
                return true;
            } else {
                if (node->median) {
                    node = node->median;
                    i++;
                } else {
                    return false;
                }
            }
        }
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    vector<string> to_ret;
    if (numCompletions == 0) {
        return to_ret;
    }
    if (root == nullptr) {
        return to_ret;
    }
    if (prefix.size() == 0) {
        return to_ret;
    }
    TierNode* curr = root;
    // int curr_word_length = prefix.length();
    vector<pair<string, int>> allTheWords;
    int i = 0;
    while (curr != nullptr) {
        if (prefix[i] < curr->singleChar) {
            curr = curr->left;
        } else if (prefix[i] > curr->singleChar) {
            curr = curr->right;
        } else {
            if (i == prefix.size()) {
                if (curr->frequency != 0) {
                    allTheWords.push_back(make_pair(prefix, curr->frequency));
                }
                break;
            }
            curr = curr->median;
            i++;
        }
    }
    traversal(curr->median, allTheWords, prefix);
    sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
    if (allTheWords.size() < numCompletions) {
        for (int k = 0; k < allTheWords.size(); k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    } else {
        for (int k = 0; k < numCompletions; k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    }
    return to_ret;
    // prefix not exist;
    /*
    if (!curr) {
        return to_ret;
    }
    if (curr->frequency != 0) {
        allTheWords.push_back(make_pair(prefix, curr->frequency));
    }
    traversal(curr->median, allTheWords, prefix);
    sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
    int k = 0;
    if (allTheWords.size() <= numCompletions) {
        for (k = 0; k < allTheWords.size(); k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    } else {
        for (k = 0; k < numCompletions; k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    }*/
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
void DictionaryTrie::traversal(TierNode* node,
                               vector<pair<string, int>>& wordsets,
                               string prefix) {
    if (node == nullptr) {
        return;
    }
    if (node->frequency != 0) {
        wordsets.push_back(
            make_pair(prefix + node->singleChar, node->frequency));
    }
    if (node->left != nullptr) {
        traversal(node->left, wordsets, prefix);

        if (node->median != nullptr) {
            traversal(node->median, wordsets, prefix + node->singleChar);
        }
        if (node->right != nullptr) {
            traversal(node->right, wordsets, prefix);
        }
    }
