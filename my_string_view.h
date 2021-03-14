#ifndef MY_STRING_VIEW_H_
#define MY_STRING_VIEW_H_

#include <limits>
#include <cstring>
#include <algorithm>
#include <stdexcept>

class StringView {
 public:
  StringView();

  explicit StringView(const char* str, int count = npos);

  int length() const;

  bool empty() const;

  const char& operator[](int index) const;

  const char& at(int index) const;

  const char* data();

  bool starts_with(StringView v) const;

  bool ends_with(StringView v) const;

  void remove_suffix(int count);
  void remove_prefix(int count);

  StringView substr(int pos, int count = npos);

  int find(StringView ch, int pos = 0);

  int find(char ch, int pos = 0);

  int compare(StringView v) const;

  bool operator==(StringView other) const;

  bool operator!=(StringView other) const;

  bool operator<(StringView other) const;

  bool operator<=(StringView other) const;

  bool operator>(StringView other) const;
  bool operator>=(StringView other) const;

  static constexpr int npos = std::numeric_limits<int>::max();

 private:
  void Check(int index) const;

  const char* pointer_;
  int count_;
};

#endif  // MY_STRING_VIEW_H_
