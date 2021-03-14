//
// Created by maksim on 6.12.20.
//

#include "my_string.h"
String::String() {
  size_ = 1;
  data_ = new char[capacity_];
  data_[0] = '\0';
}
String::String(const char* input) {
  clear();
  for (; *input != '\0'; input++) {
    Grow();
    this->push_back(*input);
  }
}
String::String(int count, char ch) {
  clear();
  for (int i = 0; i < count; i++) {
    Grow();
    this->push_back(ch);
  }
}
String::String(const String& other) {
  *this = other;
}
String::String(String&& other) noexcept {
  *this = std::move(other);
}
String& String::operator=(const String& other) {
  if (data_ != other.data_) {
    clear();
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;
    data_ = new char[capacity_];
    for (int i = 0; i < other.size_; i++) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}
String& String::operator=(String&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  size_ = other.size_;
  capacity_ = other.capacity_;
  delete[] data_;
  data_ = new char[capacity_];
  for (int i = 0; i < other.size_; i++) {
    data_[i] = other.data_[i];
  }
  other.clear();
  return *this;
}
int String::length() const {
  return size_ - 1;
}
bool String::empty() const {
  return (size_ == 1);
}
const char* String::c_str() const {
  return data_;
}
char& String::operator[](int index) {
  return data_[index];
}
char& String::front() {
  return data_[0];
}
const char& String::front() const {
  return data_[0];
}
char& String::back() {
  return data_[size_ - 2];
}
const char& String::back() const {
  return data_[size_ - 2];
}
void String::reserve(int capacity) {
  if (capacity_ >= capacity) {
    return;
  }
  capacity_ = capacity;
  char* new_data = new char[capacity_];
  for (int i = 0; i < size_; i++) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
}
void String::push_back(char ch) {
  Grow();
  data_[size_ - 1] = ch;
  size_++;
  data_[size_ - 1] = '\0';
}
void String::pop_back() {
  size_--;
  data_[size_ - 1] = '\0';
}
const char& String::operator[](int index) const {
  return data_[index];
}
void String::insert(int index, const String& str) {
  reserve(size_ + str.size_);
  for (int i = size_ - 1; i >= index; i--) {
    data_[i + str.length()] = data_[i];
  }
  for (int i = 0; i < str.length(); i++) {
    data_[i + index] = str[i];
  }
  size_ += str.size_ - 1;
  data_[size_ - 1] = '\0';
}
void String::insert(int index, const char* str, int count) {
  reserve(size_ + static_cast<int>(strlen(str)));
  for (int i = size_ - 1; i >= index; i--) {
    data_[i + count] = data_[i];
  }
  for (int i = 0; i < count; i++) {
    data_[i + index] = str[i];
  }
  size_ += count;
}
void String::erase(int index, int count) {
  count = std::min(count, size_ - 1 - index);
  for (int i = index + count; i < size_; i++) {
    data_[i - count] = data_[i];
  }
  size_ -= count;
}
String operator+(const String& lhs, const String& rhs) {
  String result = lhs;
  result += rhs;
  return result;
}
String& String::operator+=(const String& other) {
  String result;
  result.reserve(size_ + other.size_);
  std::strncpy(result.data_, data_, size_ - 1);
  std::strncpy(result.data_ + size_ - 1, other.data_, other.size_);
  result.size_ = size_ + other.size_ - 1;

  *this = result;
  return *this;
}
void String::clear() {
  delete[] data_;
  data_ = new char[capacity_];
  size_ = 1;
  data_[0] = '\0';
}
bool String::operator==(const String& other) const {
  return this->compare(other) == 0;
}
bool String::operator!=(const String& other) const {
  return this->compare(other) != 0;
}
bool String::operator<(const String& other) const {
  return this->compare(other) == -1;
}
bool String::operator<=(const String& other) const {
  return this->compare(other) != 1;
}
bool String::operator>(const String& other) const {
  return this->compare(other) == 1;
}
bool String::operator>=(const String& other) const {
  return this->compare(other) != -1;
}
bool String::operator==(const char* other) const {
  return this->compare(other) == 0;
}
bool String::operator!=(const char* other) const {
  return this->compare(other) != 0;
}
bool String::operator<(const char* other) const {
  return this->compare(other) == -1;
}
bool String::operator<=(const char* other) const {
  return this->compare(other) != 1;
}
bool String::operator>(const char* other) const {
  return this->compare(other) == 1;
}
bool String::operator>=(const char* other) const {
  return this->compare(other) != -1;
}
bool operator==(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) == 0;
}
bool operator!=(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) != 0;
}
bool operator<(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) == 1;
}
bool operator<=(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) != -1;
}
bool operator>(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) == -1;
}
bool operator>=(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) != 1;
}

int String::compare(const char* other) const {
  int k =
      strncmp(data_, other, std::min(size_, static_cast<int> (strlen(other))));

  if (k != 0) {
    if (k > 0) {
      return 1;
    }
    return -1;
  }

  if (size_ - 1 != static_cast<int>(strlen(other))) {
    return size_ - 1 < static_cast<int>(strlen(other)) ? -1 : 1;
  }
  return 0;
}
int String::compare(const String& other) const {
  int k = strncmp(data_, other.data_, std::min(size_, other.size_));
  if (k > 0) {
    return 1;
  } else if (k < 0) {
    return -1;
  }
  if (size_ - 1 != other.length()) {
    return size_ - 1 < other.length() ? -1 : 1;
  }
  return 0;
}
void String::Grow() {
  if (size_ == capacity_) {
    reserve(size_ * growth);
  }
}
String::~String() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}
