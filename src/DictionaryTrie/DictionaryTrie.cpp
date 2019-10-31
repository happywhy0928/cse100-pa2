/**
 * Overview: this file is the implementation of the DictionaryTrie.hpp
 *
 * Author:
 * Hongyu Wang    email:how025@ucsd.edu
 * Carghin Rekani  email:Crekani@ucsd.edu
 * Date: Oct 30, 2019
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

/*the comparator to compare the frequency first and set the higher
 * frequency word with higher order
 * if the frequency is equal then compare by the order of alphabet
 */
bool sortByFrequency(const pair<string, unsigned int>& x,
                     const pair<string, unsigned int>& y) {
    // if the frequency equal then compare alphabetly
    if (x.second == y.second) {
        return x.first < y.first;
    }
    // compare the frequency
    if (x.second > y.second) {
        return true;
    }
    return false;
}

/*
 * the constructor of the entry DictionaryTrie which set the root
 */
DictionaryTrie::DictionaryTrie() { root = nullptr; }
/*
 * the constructor of the TierNode which store the char in it
 * frequency are initialized set to 0 to indicate not a word
 * set the left/right/median node to nullptr
 * Parameter: the charter to store in this specific node
 */
DictionaryTrie::TierNode::TierNode(char charter) {
    frequency = 0;
    singleChar = charter;
    left = nullptr;
    median = nullptr;
    right = nullptr;
}
/*
 * the method first check if the word is already in the tree or not
 * if in the tree, then return false, if not we start to insert
 * first we go through each char to locate the position in the tree
 * if at the last char we could locate the node, the just change current
 * node 's frequency to indicate it is a word.
 * If at some point the curr is a nullptr, then we just add the new
 * TierNode for each following char
 * Parameter:
 * string word: is the word to insert inside the tree
 * unsigned int freq: to indicate the word's frequency and indicate it
 * is a word
 * Citation: using the pseudocode from the stepik
 */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    // first check if the word is already in the tree or not
    if (find(word) == true) {
        return false;
    }
    // start to loop through the tree to locate
    int count = 0;
    char currLetter = word[count];
    TierNode* curr = root;
    TierNode* inputNode = new TierNode(currLetter);
    for (;;) {
        currLetter = word[count];
        inputNode->singleChar = currLetter;
        // if  root not exist, then start to create the tree at first time
        if (root == nullptr) {
            root = inputNode;
            count = count + 1;
            while (count < word.size()) {
                currLetter = word[count];
                inputNode->median = new TierNode(currLetter);
                inputNode = inputNode->median;
                count++;
            }
            // set the word frequency to indicate it is a word
            inputNode->frequency = freq;
            break;
            // left child case
        } else if (inputNode->singleChar < curr->singleChar) {
            if (curr->left != nullptr) {
                curr = curr->left;
                // if not exist, then start to create remaining char as new
                // Tiernode
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
                // set the word frequency to indicate it is a word
                curr->frequency = freq;
                break;
            }
            // right child case
        } else if (inputNode->singleChar > curr->singleChar) {
            if (curr->right != nullptr) {
                curr = curr->right;
            }  // if not exist, then start to create remaining char as new
               // Tiernode
            else {
                curr->right = inputNode;
                curr = curr->right;
                count++;
                while (count < word.size()) {
                    currLetter = word[count];
                    curr->median = new TierNode(currLetter);
                    curr = curr->median;
                    count++;
                }
                // set the word frequency to indicate it is a word
                curr->frequency = freq;
                break;
            }
            // median child case
        } else {
            if (count == word.size() - 1) {
                curr->frequency = freq;
                return true;
            }  // if not exist, then start to create remaining char as new
               // Tiernode
            else {
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
                    // set the word frequency to indicate it is a word
                    curr->frequency = freq;
                    break;
                }
            }
        }
    }
}
/*
 *the method go through the tree to locate the word, if the node exist
 * and its frequency is not equal to zero, then the word is find
 * otherwise, either if node not exist or frequency is equal to zero
 * the word did not exist in the tree
 * parameter:
 * string word: the word to find whether or not in the tree
 * Return: return true if in the true
 *         return false if not in the true
 * Citation: the code use the pseudocode in stepik
 */
bool DictionaryTrie::find(string word) const {
    // check if the tree is empty or not
    if (root == nullptr) {
        return false;
    }
    // start to loop through
    TierNode* node = root;
    int i = 0;
    for (;;) {
        // left child case
        if (word[i] < node->singleChar) {
            if (node->left) {
                node = node->left;
            }  // not exist then return false
            else {
                return false;
            }
            // right child case
        } else if (word[i] > node->singleChar) {
            if (node->right) {
                node = node->right;
            }  // not exist then return false
            else {
                return false;
            }
        } else {
            // case we find the node is exist and frequency is not equal to 0
            if (i == word.size() - 1 && node->frequency != 0) {
                return true;
            }
            // median child case
            else {
                if (node->median) {
                    node = node->median;
                    i++;
                }  // not exist then return false
                else {
                    return false;
                }
            }
        }
    }
}

/*
 * the method first locate the prefix then travseral through the tree
 * to find all the possibles of the prediction
 * finally, we sort all the possibles and get the numCompletion's prediction
 * Parameter:
 * string prefix: the prefix to predict the following part of word
 * unsigned int numCompletions: the number of prediction to make
 * Return:
 * return the  frequency words (or in alphablet) as needed number
 * Citation:
 * using the same logic as discussion
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    vector<string> to_ret;
    // first check edge case
    if (numCompletions == 0) {
        return to_ret;
    }
    if (root == nullptr) {
        return to_ret;
    }
    if (prefix.size() == 0) {
        return to_ret;
    }
    // start to locate the prefix node
    TierNode* curr = root;
    vector<pair<string, int>> allTheWords;
    int i = 0;
    while (curr != nullptr) {
        // compare the char to go right or left
        if (prefix[i] != curr->singleChar) {
            if (prefix[i] < curr->singleChar) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        } else {
            if (++i == prefix.size()) {
                // check if the prefix itself is word or not
                if (curr->frequency != 0) {
                    allTheWords.push_back(make_pair(prefix, curr->frequency));
                }
                // start to traversal the entire subtree of prefix
                traversal(curr->median, allTheWords, prefix, numCompletions);
                // sort them in order
                sort(allTheWords.begin(), allTheWords.end(), sortByFrequency);
                break;
            }
            curr = curr->median;
        }
    }
    // get the most frequent word in order
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
}

/*
 * the method get the pattern word loop through each character
 * if any one of them is underscore, then find all the possibile and
 * continue using recursion helpmer method. Then using sorting method
 * to get them in order to get the result
 * Parameter:
 * string pattern: the word contain underscore to predict
 * unsigned int numCompletions: the number of prediction we need to make
 * Return:
 * the method return the needed number of word in order of frequency and
 * alphabet
 * Citation:
 * using the algorithm in the discussion
 */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    vector<string> result;
    // edge case
    if (numCompletions == 0) {
        return result;
    }
    if (root == nullptr) {
        return result;
    }
    if (pattern.size() == 0) {
        return result;
    }
    // start to loop through
    TierNode* curr = root;
    vector<pair<string, int>> allTheWords;
    TierNode* temp = nullptr;
    string before = "";
    int i = 0;
    while (i < pattern.length()) {
        // keep track of char if not meet underscore
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
        // if meet with underscore, then go into the recursion
        if (pattern.at(i) == '_') {
            helperUnder(curr, pattern, allTheWords, i, before);
            break;
        }
    }
    // sort all the words in order and push into the result
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
}

/*
 * delete all the TierNode in the tree calling helper method
 */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }
/*
 * helper method to recursively delete all the Tiernode in the tree
 */
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
/*
 * the helper method for predictCompletions to travseral through the prefix
 * subtree and push all the word into the wordset for further sorting
 * Parameter:
 * TierNode* node: the current node to check to push or not depending on
 * if the frequency is 0 or 1 (1 mean it is a word to push)
 * Vector<pair<string, int>>& wordsets: the wordsets to get all the word
 *                                       in the form of prefix
 * string prefix: the string to keep track of the word
 * unsigned int numCompletions: the number of prediction we need to predict
 *                  useful for optimization
 */
void DictionaryTrie::traversal(TierNode* node,
                               vector<pair<string, int>>& wordsets,
                               string prefix, unsigned int numCompletions) {
    if (node == nullptr) {
        return;
    }
    // check if the current node is a word or not
    if (node->frequency != 0) {
        wordsets.push_back(
            make_pair(prefix + node->singleChar, node->frequency));
    }
    // recursion to its left child
    if (node->left != nullptr) {
        traversal(node->left, wordsets, prefix, numCompletions);
    }
    // recursion to its median child  and keep track of the current string
    if (node->median != nullptr) {
        traversal(node->median, wordsets, prefix + node->singleChar,
                  numCompletions);
    }
    // recursion to its right child
    if (node->right != nullptr) {
        traversal(node->right, wordsets, prefix, numCompletions);
    }
}
/*
 * the helper method for predictUnderScore that when we meet a underscore
 * we search for all the possibility and include that into the result for
 * further check Parameter: TierNode* node: the current node to continue to
 * search queue<pair<TierNode*, string>>& result: which keep track the all the
 * possibility of underscore string prefix: the string to keep track in the
 * recursion
 */
void DictionaryTrie::underscoreNode(TierNode* node,
                                    queue<pair<TierNode*, string>>& result,
                                    string prefix) {
    TierNode* curr = node;
    // left child check possibility
    if (curr->left) {
        underscoreNode(curr->left, result, prefix);
    }
    // check the current node and keep track of the string
    if (curr != nullptr) {
        result.push(make_pair(curr, prefix + curr->singleChar));
    }
    // right child check possibility
    if (curr->right) {
        underscoreNode(curr->right, result, prefix);
    }
}
/*
 * the helper method for predictUnderScore that we find that if the check char
 * existed as a subnote of the curr or not, if not then current possibility
 * does not correspond to the pattern
 * Parameter:
 * char check: the char to find in all of the curr 'next character
 * TierNode* curr: the curr node to start find
 * TierNode*& result: the location of the that char existed as the sub node
 * of the current node
 *
 */
void DictionaryTrie::find1(char check, TierNode* curr, TierNode*& result) {
    if (curr == nullptr) {
        return;
    }
    TierNode* node = curr;
    int i = 0;
    for (;;) {
        // check the left child exist or not
        if (check < node->singleChar) {
            if (node->left) {
                node = node->left;
            } else {
                result = nullptr;
                return;
            }
            // check the right child exist or not
        } else if (check > node->singleChar) {
            if (node->right) {
                node = node->right;
            } else {
                result = nullptr;
                return;
            }
            // we find the sub node
        } else if (check == node->singleChar) {
            result = node;
            return;
        }
    }
}
/*
 * the helper method for predictUnderScore, when we meet a underscore
 * in the main method, we go into this helper method to keep track
 * each possibility and check if the possibility correspond to the pattern
 * Parameter:
 * TierNode* curr: the current node to continue to search
 * queue<pair<TierNode*, string>>& result: which keep track the all
 *                the word correspond to the pattern
 * string pattern: the pattern we need to check with each possibility
 *  int index: the current index we are locating and continue to check at
 * pattern
 * string before: to keep track of the chars before the current checking
 */
void DictionaryTrie::helperUnder(TierNode* curr, string pattern,
                                 vector<pair<string, int>>& allTheWords,
                                 int index, string before) {
    queue<pair<TierNode*, string>> s;
    underscoreNode(curr, s, before);
    // start the recursion and check each possibility
    while (s.empty() != true) {
        TierNode* temp = nullptr;
        pair<TierNode*, string> firstEl;
        firstEl = s.front();
        curr = firstEl.first->median;
        temp = firstEl.first;
        string prefix = firstEl.second;
        string follow = "";
        int i = index + 1;
        // we find the word in this possibility
        if (i == pattern.length() && temp->frequency != 0) {
            allTheWords.push_back(make_pair(prefix + follow, temp->frequency));
        }
        while (i < pattern.length()) {
            // follow the pattern and keep track of the char
            if (pattern.at(i) != '_') {
                temp = curr;
                find1(pattern.at(i), curr, temp);
                if (temp != nullptr) {
                    follow += pattern.at(i);
                }
                if (temp == nullptr) {
                    break;
                }
                curr = temp->median;
                // go into recursion
            } else if (pattern.at(i) == '_') {
                prefix += follow;
                if (curr) {
                    helperUnder(curr, pattern, allTheWords, i, prefix);
                }
                break;
            }
            i++;
            // we find the word in this possibility
            if (temp != nullptr) {
                if (i == pattern.length() && temp->frequency != 0) {
                    allTheWords.push_back(
                        make_pair(prefix + follow, temp->frequency));
                    break;
                }
            }
        }
        // check50 next possibility
        s.pop();
    }
}