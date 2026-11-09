#include <gtest/gtest.h>
#include "trie.h"

TEST(TrieTest, InsertAndContains) {
    Trie test;
    test.insert("apple");
    test.insert("app");

    EXPECT_TRUE(test.contains("apple"));
    EXPECT_TRUE(test.contains("app"));
    EXPECT_FALSE(test.contains("appl"));
    EXPECT_FALSE(test.contains("banana"));
    EXPECT_FALSE(test.contains(""));
}


TEST(TrieTest, EraseWorks) {
    Trie test;
    test.insert("test");
    test.insert("team");

    EXPECT_TRUE(test.contains("test"));
    EXPECT_TRUE(test.contains("team"));

    EXPECT_TRUE(test.erase("test"));
    EXPECT_FALSE(test.contains("test"));
    EXPECT_TRUE(test.contains("team"));

    EXPECT_FALSE(test.erase("nonexistent"));
    EXPECT_FALSE(test.erase("te"));
}


TEST(TrieTest, SizeAndEmpty) {
    Trie test;
    EXPECT_TRUE(test.empty());
    EXPECT_EQ(test.size(), 0);

    test.insert("hello");
    EXPECT_FALSE(test.empty());
    EXPECT_EQ(test.size(), 1);

    test.clear();
    EXPECT_TRUE(test.empty());
    EXPECT_EQ(test.size(), 0);
}


TEST(TrieTest, PrefixCountAndSize) {
    Trie test;
    EXPECT_TRUE(test.empty());
    EXPECT_EQ(test.size(), 0);

    test.insert("car");
    test.insert("card");
    test.insert("care");
    test.insert("dog");

    EXPECT_FALSE(test.empty());
    EXPECT_EQ(test.size(), 4);

    EXPECT_EQ(test.prefix_count("car"), 3);  // car, card, care
    EXPECT_EQ(test.prefix_count("ca"), 3);
    EXPECT_EQ(test.prefix_count("dog"), 1);
    EXPECT_EQ(test.prefix_count("cat"), 0);
    EXPECT_EQ(test.prefix_count(""), 4);

    test.clear();
    EXPECT_TRUE(test.empty());
    EXPECT_EQ(test.size(), 0);
}


TEST(TrieTest, WordsWithPrefix) {
    Trie test;
    test.insert("cat");
    test.insert("caterpillar");
    test.insert("category");
    test.insert("car");

    auto results = test.words_with_prefix("cat");
    // Должно найти cat, caterpillar, category (в алфавитном порядке)
    ASSERT_EQ(results.size(), 3);
    EXPECT_EQ(results[0], "cat");
    EXPECT_EQ(results[1], "category");
    EXPECT_EQ(results[2], "caterpillar");

    // Проверяем работу limit
    auto limited = test.words_with_prefix("cat", 2);
    EXPECT_EQ(limited.size(), 2);

    // Префикс, которого нет
    auto empty_res = test.words_with_prefix("dog");
    EXPECT_TRUE(empty_res.empty());
}


TEST(TrieTest, Utf8) {
    Trie test;
    test.insert("привет");
    test.insert("приставка");
    test.insert("программирование");

    EXPECT_TRUE(test.contains("привет"));
    EXPECT_TRUE(test.contains("приставка"));
    EXPECT_FALSE(test.contains("при"));

    EXPECT_EQ(test.prefix_count("при"), 2);

    auto words = test.words_with_prefix("при");
    ASSERT_EQ(words.size(), 2);
    EXPECT_EQ(words[0], "привет");
    EXPECT_EQ(words[1], "приставка");

    EXPECT_TRUE(test.erase("привет"));
    EXPECT_FALSE(test.contains("привет"));
    EXPECT_TRUE(test.contains("приставка"));
}


TEST(TrieTest, ComparisonOperators) {
    Trie t1, t2;
    t1.insert("test");
    t2.insert("test");

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);

    t2.insert("other");
    EXPECT_FALSE(t1 == t2);
    EXPECT_TRUE(t1 != t2);
}


TEST(TrieTest, CopyAndMoveSemantics) {
    Trie t1;
    t1.insert("apple");

    Trie t2(t1);
    EXPECT_TRUE(t2.contains("apple"));

    t1.erase("apple");
    EXPECT_FALSE(t1.contains("apple"));
    EXPECT_TRUE(t2.contains("apple"));

    Trie t3;
    t3 = t2;
    EXPECT_TRUE(t3.contains("apple"));

    Trie t4(std::move(t3));
    EXPECT_TRUE(t4.contains("apple"));
    EXPECT_TRUE(t3.empty());
}