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
    std::vector<std::string> to_ret;

    if (root == NULL)
        return to_ret;
    else if (prefix.empty() || prefix.length() == 0)
        return to_ret;

    // define vector the size of prefix
    std::vector<char, int> char_to_num_map;

    TierNode* curr_trie_node = root;
    int curr_word_length = prefix.length();
    char curr_char;
    // mapping the prefix as an array
    for (int i = 0; i < curr_word_length; i++) {
        curr_char = (char)prefix[i];
        int curr_node_index = char_to_num_map[curr_char];
        // int curr_node_index = (int curr_char'a')
        curr_trie_node = curr_trie_node->data[curr_node_index];
    }

    std::queue<std::pair<TierNode*, std::string>> q;

    std::vector<std::pair<std::string, int>> pairs_list;
    std::vector<std::pair<std::string, int>> to_ret;
    std::pair<TierNode*, std::string> curr_pair;
    curr_pair = {curr_trie_node, prefix};
    q.push(curr_pair);

    // Putting the root with the original prefix into the queue
    while (!q.empty()) {
        // once its stored in curr pair we pop it from queue
        curr_pair = q.front();
        q.pop();

        // reading trie and if its a word/get a word we want to push into list
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
            std::string new_pair_second = curr_pair.second + (char)(97 + i);
            new_pair = {new_pair_first, new_pair_second};
            q.push(new_pair);
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
    return to_ret;
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