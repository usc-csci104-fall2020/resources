#ifndef STR_H
#define STR_H
#include <iostream>
#include <memory>

class Str {
 public:
  Str();
  Str(const Str& other);
  Str(const char* s);
  ~Str();
  size_t size() const;
  char operator[](size_t pos) const;
  char& operator[](size_t pos) ;
  friend std::ostream& operator<<(std::ostream& os, const Str& rhs);
  Str operator+(const Str & rhs) const;
  bool operator==(const Str & rhs) const;
  Str& operator=(const Str& rhs);
  Str& operator+=(const Str& rhs);
  private:
  std::unique_ptr<char []> buffer;
  size_t len;

};

#endif
