/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() { root = nullptr; }
DictionaryTrie::TierNode::TierNode(char singleChar) {
    singleChar = singleChar;
    right = 0;
    left = 0;
    median = 0;
    frequency = 0;
    is_leaf = false;
}
/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    // first check if the word is already in the tree or not
  if (find(word) == true) {
        return false;
    }
    int i = 0;
    char currLetter = word[i];
    TierNode* curr = root;
    TierNode* inputNode = new TierNode(currLetter);
    for (;;) {
        currLetter = word[i];
        inputNode->singleChar = currLetter;
        if (root == nullptr) {
            root = inputNode;
            i = i + 1;
            currLetter = word[i];
            while (i < word.size()) {
                currLetter = word[i];
                inputNode->singleChar = currLetter;
                inputNode->median = inputNode;
                inputNode = inputNode->median;
                i = i + 1;
                currLetter = word[i];
            }
            inputNode->frequency = freq;
            break;
        } else if (inputNode->singleChar < curr->singleChar) {
            if (curr->left) {
                curr = curr->left;
            } else {
                curr->left = inputNode;
                i = i + 1;
                currLetter = word[i];
                while (i < word.size()) {
                    currLetter = word[i];
                    inputNode->singleChar = currLetter;
                    inputNode->median = inputNode;
                    inputNode = inputNode->median;
                    i = i + 1;
                    currLetter = word[i];
                }
                inputNode->frequency = freq;
                break;
            }
        } else if (inputNode->singleChar > curr->singleChar) {
            if (curr->right) {
                curr = curr->right;
            } else {
                while (i < word.size()) {
                    currLetter = word[i];
                    inputNode->singleChar = currLetter;
                    inputNode->median = inputNode;
                    inputNode = inputNode->median;
                    i = i + 1;
                    currLetter = word[i];
                }
                inputNode->frequency = freq;
                break;
            }
        } else {
            if (i == word.size() - 1) {
                curr->frequency = freq;
                return true;
            } else {
                if (curr->median) {
                    curr = curr->median;
                    i = i + 1;
                    currLetter = word[i];
                } else {
                    while (i < word.size()) {
                        inputNode->singleChar = currLetter;
                        curr->median = inputNode;
                        curr = curr->median;
                        i++;
                        currLetter = word[i];
                    }
                    curr->frequency = freq;
                    break;
                }
            }
        }
    }
}
   
/*
 */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) {
        return false;
    }
    TierNode* node = root;
    int i = 0;
    for (;;) {
        if (word.at(i) < node->singleChar) {
            if (node->left) {
                node = node->left;
            } else {
                return false;
            }
        } else if (word.at(i) > node->singleChar) {
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
    std::vector<std::string> to_ret;

    if (root == NULL)
        return to_ret;
    else if (prefix.empty() || prefix.length() == 0)
        return to_ret;
    TierNode* curr = root;
    int curr_word_length = prefix.length();
    std::vector<std::pair<std::string, int>> allTheWords;
    // char curr_char;
    // mapping the prefix as an array
    // for (int i = 0; i < curr_word_length; i++) {
    //   curr_char = (char)prefix[i];
    // int curr_node_index = char_to_num_map[curr_char];
    // int curr_node_index = (int curr_char'a')
    //   curr_trie_node = curr_trie_node->data[curr_node_index];
    // }
    int i = 0;
    while (curr && i < prefix.length()) {
        if (prefix.at(i) < curr->singleChar) {
            curr = curr->left;
        }
        if (prefix.at(i) > curr->singleChar) {
            curr = curr->right;
        }
        if (prefix.at(i) == curr->singleChar) {
            curr = curr->median;
            i++;
        }
    }
    if (!curr) {
        return to_ret;
    }

    //  std::priority_queue<std::pair<TierNode*, std::string>> q;

    /*   std::vector<std::pair<std::string, int>> pairs_list;
       std::vector<std::pair<std::string, int>> to_ret;
       std::pair<TierNode*, std::string> curr_pair;
       curr_pair = {curr_trie_node, prefix};
       // q.push(curr_pair);

         // Putting the root with the original prefix into the queue
         while (!q.empty()) {
             // once its stored in curr pair we pop it from queue
             curr_pair = q.front();
             q.pop();

             // reading trie and if its a word/get a word we want to push into
       list
             // with frequency
             if (curr_pair.first->is_leaf == true) {
                 std::pair<std::string, int> updated_pair;
                 updated_pair = {curr_pair.second, curr_pair.first->frequency};
                 pairs_list.push_back(updated_pair);
             }

             // TODO traverse TST and find words that begin with the prefix and
             // add to pairs_list , do not worry about frequency
             for (int i = 0; i <= 26; i++) {
                 if (curr_pair.first->data[i] == nullptr) continue;
                 std::pair<TierNode*, std::string> new_pair;
                 TierNode* new_pair_first = curr_pair.first->data[i];
                 std::string new_pair_second = curr_pair.second + (char)(97 +
       i); new_pair = {new_pair_first, new_pair_second}; q.push(new_pair);
             }
         }
       // sorting based on frequency to get only numCompletions of results
         std::sort(pairs_list.begin(), pairs_list.end(),
                   [](const std::pair<std::string, int>& p1,
                      const std::pair<std::string, int>& p2) {
                       return p1.second > p2.second;
                   });

       int num_added = 0;
       int curr_ind = 0;
       // adding most frequent words to the return list or the final list
       while (num_added < numCompletions && curr_ind < pairs_list.size()) {
           to_ret.push_back(pairs_list[curr_ind].first);
           num_added++;
           curr_ind++;
       }
       return to_ret;  */
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
void DictionaryTrie::traversal(TierNode* node,
                               vector<std::pair<std::string, int>>* allTheWords,
                               string prefix) {
    string newWord = prefix;
    if (node) {
        return;
    }
    if (node->left) {
        traversal(node->left, allTheWords, prefix);
    }
    if (node->median) {
        traversal(node->median, allTheWords, prefix);
    }
    if (node->right) {
        traversal(node->right, allTheWords, prefix);
    }
}
