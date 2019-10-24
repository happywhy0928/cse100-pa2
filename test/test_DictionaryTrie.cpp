/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* TODO */
TEST(DictTrieTests, insert_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.insert("a", 10), true);
    cout << "yes";
    ASSERT_EQ(dict.insert("b", 10), true);
    ASSERT_EQ(dict.insert("b", 10), false);
    ASSERT_EQ(dict.find("a"), true);
    ASSERT_EQ(dict.find("abcc"), false);
    ASSERT_EQ(dict.find("b"), true);
    ASSERT_EQ(dict.insert("ab", 25), true);
    ASSERT_EQ(dict.find("ab"), true);
}
TEST(DictTrieTests, predict_TEST) {
    DictionaryTrie dict;
    dict.insert("cat", 1);
    dict.insert("cank", 16);
    dict.insert("caaatkkk", 322);
    dict.insert("cant", 16);
    dict.insert("dog", 2425);
    dict.insert("fly", 322);
    vector<string> result = dict.predictCompletions("ca", 3);
    ASSERT_EQ(result[0], "caaatkkk");
    ASSERT_EQ(result[1], "cank");
    ASSERT_EQ(result[2], "cant");
}