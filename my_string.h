#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <stdexcept>
#include <compare>

class String {
 public:
  String();

  explicit String(const char* input);

  String(int count, char ch);

  String(const String& other);
  String& operator=(const String& other);

  String(String&& other) noexcept;
  String& operator=(String&& other) noexcept;

  int length() const;
  bool empty() const;
  const char* c_str() const;

  ~String();

  char& operator[](int index);
  const char& operator[](int index) const;

  char& front();
  const char& front() const;

  char& back();
  const char& back() const;

  void reserve(int capacity);

  void push_back(char ch);
  void pop_back();

  void insert(int index, const String& str);
  void insert(int index, const char* str, int count);

  void erase(int index, int count = 1);

  friend String operator+(const String& lhs, const String& rhs);
  String& operator+=(const String& other);

  void clear();

  int compare(const String& other) const;
  int compare(const char* other) const;

  bool operator==(const String& other) const;
  bool operator!=(const String& other) const;

  bool operator<(const String& other) const;
  bool operator<=(const String& other) const;
  bool operator>(const String& other) const;
  bool operator>=(const String& other) const;

  bool operator==(const char* other) const;
  bool operator!=(const char* other) const;
  bool operator<(const char* other) const;
  bool operator<=(const char* other) const;
  bool operator>(const char* other) const;
  bool operator>=(const char* other) const;

  friend bool operator==(const char* lhs, const String& rhs);
  friend bool operator!=(const char* lhs, const String& rhs);
  friend bool operator<(const char* lhs, const String& rhs);
  friend bool operator<=(const char* lhs, const String& rhs);
  friend bool operator>(const char* lhs, const String& rhs);
  friend bool operator>=(const char* lhs, const String& rhs);

 private:
  void Grow();

  int size_;
  int capacity_{5};
  char* data_{nullptr};

  static const int growth = 2;
};

#endif  // MY_STRING_H_
