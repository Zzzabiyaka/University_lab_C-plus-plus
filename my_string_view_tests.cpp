#include "my_string_view.h"
#include <gtest/gtest.h>

TEST(StringView, Basic) {
  StringView a;
  EXPECT_EQ(a.data(), nullptr);
}

TEST(StringView, Constructors) {
  StringView actual("abc", 2);

  EXPECT_EQ(actual.data(), "abc");
  EXPECT_EQ(actual.length(), 2);
  EXPECT_FALSE(actual.empty());
}

TEST(StringView, IndexOperatorAndAt) {
  StringView actual("abc", 2);
  EXPECT_EQ(actual[0], 'a');
  EXPECT_EQ(actual[1], 'b');

  EXPECT_ANY_THROW(actual.at(15));
}

TEST(StringView, StartsWithAndEndsWith) {
  StringView actual("abc", 3);
  StringView a1("a");
  StringView a2("ab");

  EXPECT_TRUE(actual.starts_with(a1));
  EXPECT_TRUE(actual.starts_with(a2));

  EXPECT_FALSE(actual.ends_with(a1));
  EXPECT_FALSE(actual.ends_with(a2));
}

TEST(StringView, Substr) {
  StringView actual("abcdefg");

  StringView actual_second = actual.substr(1, 3);
  StringView expected("bcd");
  EXPECT_EQ(actual_second, expected);
}

TEST(StringView, Find) {
  StringView actual("abcabcabc");

  StringView temp("bc");

  EXPECT_EQ(actual.find('a'), 0);

  EXPECT_EQ(actual.find(temp), 1);
  EXPECT_EQ(actual.find(temp, 3), 4);

  EXPECT_EQ(actual.find('a', 2), 3);
}

TEST(StringView, RemovePrefixRemoveSuffix) {
  StringView actual("abcd");
  StringView actual1("bcd");
  StringView actual2("cd");
  StringView actual3("c");

  actual.remove_prefix(1);
  EXPECT_EQ(actual, actual1);

  actual.remove_prefix(1);
  EXPECT_EQ(actual, actual2);

  actual.remove_suffix(1);
  EXPECT_EQ(actual, actual3);
}

TEST(StringView, Comparison) {
  StringView actual("ab");
  StringView actual2("abc");
  StringView actual3("zz");

  EXPECT_TRUE(actual == actual);
  EXPECT_TRUE(actual.compare(actual) == 0);
  EXPECT_TRUE(actual < actual2);
  EXPECT_TRUE(actual.compare(actual2) == -1);
  EXPECT_TRUE(actual3 > actual);
  EXPECT_TRUE(actual3.compare(actual) == 1);
}