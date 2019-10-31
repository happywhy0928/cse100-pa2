/**
 * Overview: this file illustrate the method and class we use for
 * DictionaryTrie
 *
 * Author:
 * Hongyu Wang    email:how025@ucsd.edu
 * Carghin Rekani  email:Crekani@ucsd.edu
 * Date: Oct 30, 2019
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
    /*the Node exist in the Tree
     *member: singleChar: that each node store a single Character
     * frequency: to set it is a word or not also indicate frequency
     * left,median,right three children of current node
     */
    class TierNode {
      public:
        char singleChar;
        int frequency;
        TierNode* left;
        TierNode* median;
        TierNode* right;
        // the constructor for the TierNode to set the char
        TierNode(char charter);
    };
    // the start point of the entire true;
    TierNode* root;
    /*
     * helper method to recursively delete all the Tiernode in the tree
     */
    void deleteAll(TierNode* node);
    /*
     * the helper method for predictCompletions to travseral through the prefix
     * subtree and push all the word into the wordset for further sorting
     */
    void traversal(TierNode* node, vector<pair<string, int>>& wordsets,
                   string prefix, unsigned int numCompletions);
    /*
     * the helper method for predictUnderScore that we find that if the check
     * char existed as a subnote of the curr or not, if not then current
     * possibility does not correspond to the pattern
     */
    void find1(char check, TierNode* curr, TierNode*& result);
    /*
     * the helper method for predictUnderScore that when we meet a underscore
     * we search for all the possibility and include that into the result for
     * further check
     */
    void underscoreNode(TierNode* node, queue<pair<TierNode*, string>>& result,
                        string prefix);
    /*
     * the helper method for predictUnderScore, when we meet a underscore
     * in the main method, we go into this helper method to keep track
     * each possibility and check if the possibility correspond to the pattern
     */
    void helperUnder(TierNode* curr, string pattern,
                     vector<pair<string, int>>& allTheWords, int index,
                     string before);

  public:
    /*
     * the constructor of the entry DictionaryTrie which set the root
     */
    DictionaryTrie();

    /*
     * to insert the certain word into the tree
     * specific implementation illustrated in the DictionaryTrie.cpp
     */
    bool insert(string word, unsigned int freq);

    /*
     * to find the certain word from the tree
     * specific implementation illustrated in the DictionaryTrie.cpp
     */
    bool find(string word) const;

    /*
     * the method first locate the prefix then travseral through the tree
     * to find all the possibles of the prediction
     * finally, we sort all the possibles and get the numCompletion's prediction
     */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /*
     * the method get the pattern word loop through each character
     * if any one of them is underscore, then find all the possibile and
     * continue using recursion helpmer method. Then using sorting method
     * to get them in order to get the result
     */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /*
     * delete all the TierNode in the tree calling helper method
     */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
