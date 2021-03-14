#include "my_string.h"

#include <gtest/gtest.h>

TEST(String, Basics) {
  String actual;
  EXPECT_TRUE(actual == "");
  EXPECT_EQ(actual.length(), 0);
  EXPECT_TRUE(actual.empty());
}

TEST(String, Constructors) {
  String a("42");

  EXPECT_EQ(a, "42");
  EXPECT_EQ(a.length(), 2);
  EXPECT_FALSE(a.empty());

  String b(a);
  EXPECT_EQ(a, "42");
  EXPECT_EQ(a.length(), 2);
  EXPECT_FALSE(a.empty());
}

TEST(String, AssignmentOperators) {
  {
    String a("42");
    String b = a;

    EXPECT_EQ(a, "42");
    EXPECT_EQ(a.length(), 2);
    EXPECT_FALSE(a.empty());

    EXPECT_EQ(b, "42");
    EXPECT_EQ(b.length(), 2);
    EXPECT_FALSE(b.empty());

    String c(12, 'F');

    EXPECT_EQ(c, "FFFFFFFFFFFF");
    EXPECT_EQ(c.length(), 12);
    EXPECT_FALSE(c.empty());
  }

  {
    String a("move");
    String b = std::move(a);

    EXPECT_EQ(b, "move");
    EXPECT_EQ(b.length(), 4);

    b = std::move(b);

    EXPECT_EQ(b, "move");
    EXPECT_EQ(b.length(), 4);

    EXPECT_EQ(a, "");
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.length(), 0);
  }
}

TEST(String, IndexOperatorAndFrontBack) {
  {
    String actual("ervtbunium,mnbgvrfe");

    EXPECT_EQ(actual[0], 'e');
    EXPECT_EQ(actual[2], 'v');
    EXPECT_EQ(actual[10], ',');
    EXPECT_EQ(actual[19], '\0');

    EXPECT_EQ(actual.front(), 'e');
    actual.front() = 'z';
    EXPECT_EQ(actual.front(), 'z');

    EXPECT_EQ(actual.back(), 'e');
    actual.back() = 'z';
    EXPECT_EQ(actual.back(), 'z');
  }

  {
    String a;
    EXPECT_EQ(a[0], '\0');
  }

  {
    const String const_actual("ervtbunium,mnbgvrfe");

    EXPECT_EQ(const_actual[0], 'e');
    EXPECT_EQ(const_actual[2], 'v');
    EXPECT_EQ(const_actual[10], ',');
    EXPECT_EQ(const_actual[19], '\0');

    EXPECT_EQ(const_actual.front(), 'e');
    EXPECT_EQ(const_actual.back(), 'e');
  }
}

TEST(String, PushPop) {
  String actual;
  actual.push_back('F');

  EXPECT_EQ(actual, "F");
  actual.push_back('z');

  EXPECT_EQ(actual, "Fz");

  actual.pop_back();
  EXPECT_EQ(actual, "F");
  actual.pop_back();
  EXPECT_EQ(actual, "");
}

TEST(String, Plus) {
  String a("abc");
  String b("abc");

  a += a;
  EXPECT_EQ(a, "abcabc");

  a += a;
  EXPECT_EQ(a, "abcabcabcabc");

  a += b;
  EXPECT_EQ(a, "abcabcabcabcabc");

  String c("F");

  String d = b + c;
  String e = c + b;

  EXPECT_EQ(d, "abcF");
  EXPECT_EQ(e, "Fabc");
}

TEST(String, InsertErase) {
  String a("abacaba");

  a.insert(0, "dd", 2);
  EXPECT_EQ(a, "ddabacaba");

  String b(a);

  a.insert(1, b);
  EXPECT_EQ(a, "dddabacabadabacaba");

  a.erase(0, 3);
  EXPECT_EQ(a, "abacabadabacaba");

  a.erase(0, a.length());
  EXPECT_EQ(a, "");
}

TEST(String, Compare) {
  String a("Abacaba");

  EXPECT_EQ(a.compare("A"), 1);
  EXPECT_EQ(a.compare("Abacaba"), 0);
  EXPECT_EQ(a.compare("Abacabadaba"), -1);

  EXPECT_TRUE(a >"A");
  EXPECT_TRUE(a >= "A");
  EXPECT_TRUE(a != "A");
  EXPECT_TRUE(a == "Abacaba");
  EXPECT_TRUE(a <= "Abacaba");
  EXPECT_TRUE(a >= "Abacaba");
  EXPECT_FALSE(a != "Abacaba");

  EXPECT_TRUE("A" < a);
  EXPECT_TRUE("A" <= a);
  EXPECT_TRUE("A" != a);
  EXPECT_TRUE("Abacaba" == a);
  EXPECT_TRUE("Abacaba" >= a);
  EXPECT_TRUE("Abacaba" <= a);
  EXPECT_FALSE("Abacaba" != a);

  String b("Abacaba");
  String c("A");
  String d("Abacabadaba");

  EXPECT_EQ(a.compare(c), 1);
  EXPECT_EQ(a.compare(b), 0);
  EXPECT_EQ(a.compare(d), -1);

  EXPECT_TRUE(a > c);
  EXPECT_TRUE(a >= c);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a <= b);
  EXPECT_TRUE(a >= b);
  EXPECT_FALSE(a != b);
}

TEST(String, c_str) {
  String a("abacaba");
  const char* b = a.c_str();
  EXPECT_EQ(a.c_str(), b);
}