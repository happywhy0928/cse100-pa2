/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
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
        //   bool is_word;
        // std::vector<TierNode*> data;
        TierNode(char charter);

        // frequency(0), singleChar(singleChar) {}
        //  left(nullptr),
        // median(nullptr),
        // right(nullptr)
    };
    TierNode* root;
    void deleteAll(TierNode* node);
    void traversal(TierNode* node, vector<pair<string, int>>& wordsets,
                   string prefix, unsigned int numCompletions);
    void find1(char check, TierNode* curr, TierNode*& result);
    void underscoreNode(TierNode* node, queue<pair<TierNode*, string>>& result,
                        string prefix);
    void helperUnder(TierNode* curr, string pattern,
                     vector<pair<string, int>>& allTheWords, int index,
                     string before);

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
