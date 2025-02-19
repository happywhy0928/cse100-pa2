/**
 * Overview: this file take unit test to each method
 *
 * Author:
 * Hongyu Wang    email:how025@ucsd.edu
 * Carghin Rekani  email:Crekani@ucsd.edu
 * Date: Oct 30, 2019
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

/* check insert */

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
    dict.insert("dog", 2425);
    dict.insert("doges", 245);
}
// test simple predict
TEST(DictTrieTests, predict_TEST) {
    DictionaryTrie dict;
    dict.insert("cat", 1);
    dict.insert("ca", 1);
    dict.insert("cank", 16);
    dict.insert("caaatkkk", 322);
    dict.insert("cant", 16);
    dict.insert("dog", 2425);
    dict.insert("flight", 322);
    dict.insert("fly", 322);
    dict.insert("we", 13);
    vector<string> result = dict.predictCompletions("ca", 3);
    ASSERT_EQ(result[0], "caaatkkk");
    ASSERT_EQ(result[1], "cank");
    ASSERT_EQ(result[2], "cant");
}
// test underscore with one wildcard
TEST(DictTrieTests, underscore_TEST) {
    DictionaryTrie dict;
    dict.insert("cat", 1);
    dict.insert("cank", 16);
    dict.insert("caaatkkk", 322);
    dict.insert("cant", 16);
    dict.insert("dog", 2425);
    dict.insert("flight", 322);
    dict.insert("fly", 322);
    dict.insert("we", 13);
    dict.insert("a", 13);
    dict.insert("b", 14);
    dict.insert("c", 15);
    dict.insert("g", 10);
    dict.insert("h", 10);
    vector<string> result = dict.predictUnderscores("_", 3);
    ASSERT_EQ(result[0], "c");
    ASSERT_EQ(result[1], "b");
    ASSERT_EQ(result[2], "a");
}
// test only one underscore case
TEST(DictTrieTests, underscore_TEST1) {
    DictionaryTrie dict;
    dict.insert("ca", 13);
    dict.insert("bc", 14);
    dict.insert("aa", 15);
    vector<string> result1 = dict.predictUnderscores("_a", 2);
    ASSERT_EQ(result1[0], "aa");
    ASSERT_EQ(result1[1], "ca");
}
// test only one underscore case
TEST(DictTrieTests, underscore_TEST2) {
    DictionaryTrie dict;
    dict.insert("caa", 13);
    dict.insert("bac", 14);
    dict.insert("aac", 15);
    dict.insert("baa", 12);
    dict.insert("aaa", 15);
    dict.insert("daa", 14);
    vector<string> result1 = dict.predictUnderscores("_aa", 3);
    ASSERT_EQ(result1[0], "aaa");
    ASSERT_EQ(result1[1], "daa");
    ASSERT_EQ(result1[2], "caa");
}
// test only one underscore case
TEST(DictTrieTests, underscore_TEST4) {
    DictionaryTrie dict;
    dict.insert("acaa", 13);
    dict.insert("bac", 14);
    dict.insert("aac", 15);
    dict.insert("baa", 14);
    dict.insert("aaa", 15);
    dict.insert("daa", 10);
    dict.insert("aaaa", 15);
    dict.insert("adaa", 10);
    vector<string> result1 = dict.predictUnderscores("a_aa", 3);
    ASSERT_EQ(result1[1], "acaa");
    ASSERT_EQ(result1[2], "adaa");
    ASSERT_EQ(result1[0], "aaaa");
}
// test only one underscore case
TEST(DictTrieTests, underscore_TEST3) {
    DictionaryTrie dict;
    dict.insert("caa", 13);
    dict.insert("bac", 14);
    dict.insert("aac", 15);
    dict.insert("daa", 14);
    dict.insert("aaa", 15);
    dict.insert("faa", 10);
    dict.insert("adaa", 10);
    dict.insert("aaaa", 9);
    vector<string> result1 = dict.predictUnderscores("_aa", 3);
    ASSERT_EQ(result1[0], "aaa");
    ASSERT_EQ(result1[1], "daa");
    ASSERT_EQ(result1[2], "caa");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST6) {
    DictionaryTrie dict;
    dict.insert("aaa", 13);
    dict.insert("aba", 15);
    dict.insert("aca", 10);
    dict.insert("adaa", 10);
    dict.insert("aaaa", 9);
    vector<string> result1 = dict.predictUnderscores("__a", 3);
    ASSERT_EQ(result1[0], "aba");
    ASSERT_EQ(result1[1], "aaa");
    ASSERT_EQ(result1[2], "aca");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST7) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaca", 10);
    dict.insert("adaa", 10);
    dict.insert("caa", 13);
    dict.insert("bac", 14);
    dict.insert("aac", 15);
    dict.insert("daa", 14);
    dict.insert("aaa", 15);
    dict.insert("faa", 10);
    vector<string> result1 = dict.predictUnderscores("a__a", 3);
    ASSERT_EQ(result1[0], "aaba");
    ASSERT_EQ(result1[1], "aaaa");
    ASSERT_EQ(result1[2], "aaca");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST8) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaca", 10);
    dict.insert("adaa", 10);
    dict.insert("caa", 13);
    dict.insert("bac", 14);
    dict.insert("aac", 15);
    dict.insert("daa", 14);
    dict.insert("aaa", 15);
    dict.insert("faa", 10);
    dict.insert("aa", 11);
    dict.insert("ab", 12);
    dict.insert("ac", 9);
    dict.insert("cc", 10);
    vector<string> result1 = dict.predictUnderscores("__", 3);
    ASSERT_EQ(result1[0], "ab");
    ASSERT_EQ(result1[1], "aa");
    ASSERT_EQ(result1[2], "cc");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST9) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaca", 10);
    dict.insert("accb", 10);
    dict.insert("acca", 8);
    vector<string> result1 = dict.predictUnderscores("a__a", 3);
    ASSERT_EQ(result1[0], "aaba");
    ASSERT_EQ(result1[1], "aaaa");
    ASSERT_EQ(result1[2], "aaca");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST10) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaca", 10);
    dict.insert("accb", 10);
    dict.insert("acca", 8);
    vector<string> result1 = dict.predictUnderscores("_a_a", 3);
    ASSERT_EQ(result1[0], "aaba");
    ASSERT_EQ(result1[1], "aaaa");
    ASSERT_EQ(result1[2], "aaca");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST11) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaca", 10);
    dict.insert("accb", 10);
    dict.insert("acca", 8);
    vector<string> result1 = dict.predictUnderscores("aa__", 3);
    ASSERT_EQ(result1[0], "aaba");
    ASSERT_EQ(result1[1], "aaaa");
    ASSERT_EQ(result1[2], "aaca");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST12) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaac", 10);
    dict.insert("accb", 10);
    dict.insert("acca", 8);
    vector<string> result1 = dict.predictUnderscores("_aa_", 3);
    ASSERT_EQ(result1[0], "aaaa");
    ASSERT_EQ(result1[1], "aaac");
}
// test two underscore case
TEST(DictTrieTests, underscore_TEST13) {
    DictionaryTrie dict;
    dict.insert("aaaa", 13);
    dict.insert("aaba", 15);
    dict.insert("aaac", 10);
    dict.insert("accb", 10);
    dict.insert("acca", 8);
    dict.insert("faah", 20);
    dict.insert("gaac", 25);
    dict.insert("xaay", 19);
    vector<string> result1 = dict.predictUnderscores("_aa_", 3);
    ASSERT_EQ(result1[0], "gaac");
    ASSERT_EQ(result1[1], "faah");
    ASSERT_EQ(result1[2], "xaay");
}