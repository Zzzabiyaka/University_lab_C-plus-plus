#include "my_string_view.h"

StringView::StringView() {
  pointer_ = nullptr;
  count_ = 0;
}
StringView::StringView(const char* str, int count) {
  count_ = std::min(static_cast<int>(strlen(str)), count);
  pointer_ = str;
}
int StringView::length() const {
  return count_;
}
bool StringView::empty() const {
  return (count_ == 0);
}
const char& StringView::operator[](int index) const {
  return *(pointer_ + index);
}
const char& StringView::at(int index) const {
  Check(index);
  return *(pointer_ + index);
}
const char* StringView::data() {
  return pointer_;
}
bool StringView::starts_with(StringView v) const {
  if (v.count_ > this->count_) {
    return false;
  }
  for (int i = 0; i < v.count_; i++) {
    if (*(pointer_ + i) != *(v.pointer_ + i)) {
      return false;
    }
  }
  return true;
}
bool StringView::ends_with(StringView v) const {
  if (v.count_ > this->count_) {
    return false;
  }
  for (int i = count_ - v.count_; i < count_; i++) {
    if (*(pointer_ + i) != *(v.pointer_ + i + v.count_ - count_)) {
      return false;
    }
  }
  return true;
}
void StringView::remove_suffix(int count) {
  count_ -= count;
}
void StringView::remove_prefix(int count) {
  pointer_ += count;
  count_ -= count;
}
int StringView::find(StringView ch, int pos) {
  for (int i = pos; i + ch.count_ - 1 < count_; i++) {
    bool found = true;
    for (int j = 0; j < ch.count_; j++) {
      if (*(pointer_ + i + j) != *(ch.pointer_ + j)) {
        found = false;
      }
    }
    if (found) {
      return i;
    }
  }
  return npos;
}
int StringView::find(char ch, int pos) {
  for (int i = pos; i < count_; i++) {
    if (*(pointer_ + i) == ch) {
      return i;
    }
  }
  return npos;
}
int StringView::compare(StringView v) const {
  for (int i = 0; i < std::min(count_, v.count_); i++) {
    if (*(pointer_ + i) != *(v.pointer_ + i)) {
      if (*(pointer_ + i) < *(v.pointer_ + i)) {
        return -1;
      }
      return 1;
    }
  }
  if (count_ != v.count_) {
    if (count_ < v.count_) {
      return -1;
    }
    return 1;
  }
  return 0;
}
bool StringView::operator==(StringView other) const {
  return this->compare(other) == 0;
}
bool StringView::operator!=(StringView other) const {
  return !(*this == other);
}
bool StringView::operator<(StringView other) const {
  return this->compare(other) == -1;
}
bool StringView::operator<=(StringView other) const {
  return this->compare(other) != 1;
}
bool StringView::operator>(StringView other) const {
  return this->compare(other) == 1;
}
bool StringView::operator>=(StringView other) const {
  return this->compare(other) != -1;
}
void StringView::Check(int index) const {
  if (index >= count_ || index < 0) {
    throw std::out_of_range("Invalid index");
  }
}
StringView StringView::substr(int pos, int count) {
  StringView result;
  result.pointer_ = pointer_ + pos;
  result.count_ = std::min(count, length() - pos);
  return result;
}
