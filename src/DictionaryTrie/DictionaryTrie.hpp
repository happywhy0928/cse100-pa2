/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    class TierNode {
      public:
        char singleChar;
        int frequency;
        TierNode* left;
        TierNode* median;
        TierNode* right;
        bool is_leaf;
        std::vector<TrieNode*> data;

        TierNode(char singleChar) : frequency(0), singleChar(singleChar) {}
        //  left(nullptr),
        // median(nullptr),
        // right(nullptr)
    };
    TierNode* root;
    void deleteAll(TierNode* node);

  public:
    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
