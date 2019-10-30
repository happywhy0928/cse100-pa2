/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
bool sortByFrequency(const pair<string, unsigned int>& x,
                     const pair<string, unsigned int>& y) {
    if (x.second == y.second) {
        return x.first < y.first;
    }
    if (x.second > y.second) {
        return true;
    }
    return false;
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
            break;
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
                break;
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
                break;
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
                        curr->median = new TierNode(currLetter);
                        curr = curr->median;
                        count++;
                    }
                    curr->frequency = freq;
                    break;
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
        if (prefix[i] != curr->singleChar) {
            if (prefix[i] < curr->singleChar) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        } else {
            if (++i == prefix.size()) {
                if (curr->frequency != 0) {
                    allTheWords.push_back(make_pair(prefix, curr->frequency));
                }
                traversal(curr->median, allTheWords, prefix, numCompletions);
                sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
                break;
            }
            curr = curr->median;
            // i++;
        }
    }
    // traversal(curr->median, allTheWords, prefix, numCompletions);
    // sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
    if (allTheWords.size() < numCompletions) {
        for (int k = 0; k < allTheWords.size(); k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    } else {
        for (int k = 0; k < numCompletions; k++) {
            to_ret.push_back(allTheWords[k].first);
        }
    }
    /*   for (int k = 0; k < allTheWords.size(); k++) {
           to_ret.push_back(allTheWords[k].first);
       } */
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
    vector<string> result;
    if (numCompletions == 0) {
        return result;
    }
    if (root == nullptr) {
        return result;
    }
    if (pattern.size() == 0) {
        return result;
    }
    queue<pair<TierNode*, string>> s;
    // int i = 0;
    TierNode* curr = root;
    // string check;
    vector<pair<string, int>> allTheWords;
    TierNode* temp = nullptr;
    //   int k = 0;

    string before = "";
    int i = 0;
    while (i < pattern.length()) {
        if (pattern.at(i) != '_') {
            temp = curr;
            find1(pattern.at(i), curr, temp);
            if (temp != nullptr) {
                before += pattern.at(i);
            }
            if (temp == nullptr) {
                return result;
            }
            curr = temp->median;
            i++;
        }
        if (pattern.at(i) == '_') {
            helperUnder(curr, pattern, allTheWords, i, before);
            break;
        }
        /*
            string before = "";
            if (pattern.at(k) != '_') {
                temp = curr;
                find1(pattern.at(k), curr, temp);
                if (temp != nullptr) {
                    before += pattern.at(k);
                }
                if (temp == nullptr) {
                    return result;
                }
                curr = temp->median;
                k++;
            }
            if (pattern.at(k) == '_') {
                underscoreNode(curr, s, before);
                while (s.empty() != true) {
                    pair<TierNode*, string> firstEl;
                    firstEl = s.front();
                    curr = firstEl.first->median;
                    temp = firstEl.first;
                    string prefix = firstEl.second;
                    // prefix += firstEl.first->singleChar;
                    string follow = "";
                    // int i = k + 1;
                    int i;
                    //     int fault = 1;
                    for (i = k + 1; i < pattern.length(); i++) {
                        // curr = firstEl.first;`awq1
                        temp = curr;
                        find1(pattern.at(i), curr, temp);
                        if (temp != nullptr && temp->singleChar ==
           pattern.at(i)) { follow += pattern.at(i);
                        }
                        if (temp == nullptr) {
                            break;
                        }
                        curr = temp->median;
                    }
                    if (temp != nullptr) {
                        if (i == pattern.length() && temp->frequency != 0) {
                            allTheWords.push_back(
                                make_pair(prefix + follow, temp->frequency));
                        }
                    }
                    s.pop();
                }
            }
            */
        sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
        if (allTheWords.size() < numCompletions) {
            for (int k = 0; k < allTheWords.size(); k++) {
                result.push_back(allTheWords[k].first);
            }
        } else {
            for (int k = 0; k < numCompletions; k++) {
                result.push_back(allTheWords[k].first);
            }
        }
        return result;

        /*
        // for (i = 0; i < pattern.length() - 1; i++) {
        while (i < pattern.length() - 1) {
            if (pattern.at(i) != '_') {
                TierNode* temp;
                find1(pattern.at(i), curr, temp);
                if (temp != nullptr) {
                    s.push(make_pair(temp, check + temp->singleChar));
                    curr = temp->median;
                    check += temp->singleChar;
                }
            } else if (pattern.at(i) == '_') {
                if (curr != nullptr) {
                    underscoreNode(curr, s, check);
                }
                while (s.empty() != true) {
                    pair<TierNode*, string> checking = s.front();
                    curr = checking.first;
                    check = checking.second;
                    continue;
                }
            }
            vector<pair<string, int>> allTheWords;
        }
        return {}; */
    }

    /* delete recursively
     */
    DictionaryTrie::~DictionaryTrie() { deleteAll(root); }
    void DictionaryTrie::deleteAll(TierNode * node) {
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
    void DictionaryTrie::traversal(TierNode * node,
                                   vector<pair<string, int>> & wordsets,
                                   string prefix, unsigned int numCompletions) {
        if (node == nullptr) {
            return;
        }
        if (node->frequency != 0) {
            //  if (wordsets.size() < numCompletions) {
            wordsets.push_back(
                make_pair(prefix + node->singleChar, node->frequency));
            /*   } else {
                   sort(wordsets.begin(), wordsets.end(), sortByFrequency);
                   pair<string, int> check = wordsets.back();
                   vector<pair<string, int>> compareTwo;
                   compareTwo.push_back(check);
                   compareTwo.push_back(
                       make_pair(prefix + node->singleChar, node->frequency));
                   sort(compareTwo.begin(), compareTwo.end(), sortByFrequency);
                   wordsets.pop_back();
                   check = compareTwo.front();
                   wordsets.push_back(check);
               } */
        }
        if (node->left != nullptr) {
            traversal(node->left, wordsets, prefix, numCompletions);
        }
        if (node->median != nullptr) {
            traversal(node->median, wordsets, prefix + node->singleChar,
                      numCompletions);
        }
        if (node->right != nullptr) {
            traversal(node->right, wordsets, prefix, numCompletions);
        }
    }

    void DictionaryTrie::underscoreNode(TierNode * node,
                                        queue<pair<TierNode*, string>> & result,
                                        string prefix) {
        TierNode* curr = node;
        if (curr->left) {
            underscoreNode(curr->left, result, prefix);
        }
        if (curr != nullptr) {
            result.push(make_pair(curr, prefix + curr->singleChar));
        }
        if (curr->right) {
            underscoreNode(curr->right, result, prefix);
        }
    }
    void DictionaryTrie::find1(char check, TierNode* curr, TierNode*& result) {
        if (curr == nullptr) {
            return;
        }
        TierNode* node = curr;
        int i = 0;
        for (;;) {
            if (check < node->singleChar) {
                if (node->left) {
                    node = node->left;
                } else {
                    result = nullptr;
                    return;
                }
            } else if (check > node->singleChar) {
                if (node->right) {
                    node = node->right;
                } else {
                    result = nullptr;
                    return;
                }
            } else if (check == node->singleChar) {
                result = node;
                return;
            }
        }
    }
    void DictionaryTrie::helperUnder(TierNode * curr, string pattern,
                                     vector<pair<string, int>> & allTheWords,
                                     int index, string before) {
        queue<pair<TierNode*, string>> s;
        underscoreNode(curr, s, before);
        while (s.empty() != true) {
            TierNode* temp = nullptr;
            pair<TierNode*, string> firstEl;
            firstEl = s.front();
            curr = firstEl.first->median;
            temp = firstEl.first;
            string prefix = firstEl.second;
            string follow = "";
            // int i = k + 1;
            int i = index;
            //     int fault = 1;
            for (i = index; i < pattern.length(); i++) {
                // curr = firstEl.first;`awq1
                if (pattern.at(i) != '_') {
                    temp = curr;
                    find1(pattern.at(i), curr, temp);
                    if (temp != nullptr && temp->singleChar == pattern.at(i)) {
                        follow += pattern.at(i);
                    }
                    if (temp == nullptr) {
                        break;
                    }
                    curr = temp->median;
                }
                if (pattern.at(i) == "_") {
                    helperUnder(curr, pattern, alltheWords, i, before);
                }
            }
        }
    }