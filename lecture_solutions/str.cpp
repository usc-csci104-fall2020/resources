#include <iostream>
#include <string.h>
//#include <cstring>
#include <stdexcept>
#include <memory>
//#include <algorithm>
#include "str_sol.h"

Str::Str()
{
   buffer = std::make_unique<char []>(1);
   buffer[0] = '\0'; 
   len = 0;
}

Str::Str(const char* s)
{
    len = strlen(s);
    buffer = std::make_unique<char[]>(len+1);
 //   std::copy(s,s+len+1, buffer.get());
    strcpy(buffer.get(), s);
}

Str::Str(const Str& other){
   buffer = std::make_unique<char[]>(other.size()+1);
   len = other.size();
   //std::copy(other.buffer.get(),other.buffer.get()+len+1, buffer.get());
   strcpy(this->buffer.get(), other.buffer.get());

}

Str::~Str()
{

}

// length not including null character
size_t Str::size() const
{
  return len;
} 

char& Str::operator[](size_t pos)  {
     // should probably be an exception
     if(pos >= len) return buffer[len];
     return buffer[pos];
}

char Str::operator[](size_t pos) const {
     // should probably be an exception
     if(pos >= len) return buffer[len];
     return buffer[pos];
}

std::ostream& operator<<(std::ostream& os, const Str& rhs){

      os << rhs.buffer.get();
      return os;
}

bool Str::operator==(const Str& rhs) const{
    return (strcmp(this->buffer.get(), rhs.buffer.get()) == 0);
}

Str Str::operator+(const Str& rhs) const{
      size_t lhs_l = this->size();
      size_t rhs_l = rhs.size();
      std::unique_ptr<char []> temp = std::make_unique<char []>(lhs_l+rhs_l+1);
    // std::copy(this->buffer.get(), this->buffer.get()+lhs_l, temp.get());
     //std::copy(rhs.buffer.get(),rhs.buffer.get()+rhs_l, temp.get()+lhs_l);
      strncat(temp.get(),this->buffer.get(),lhs_l);
      strncat(temp.get()+lhs_l, rhs.buffer.get(), rhs_l);
      Str result(temp.get());
      return result;
}

Str& Str::operator=(const Str& rhs){
//     if (&rhs == this) return *this;
     if (&rhs == this) return *this;
   buffer = std::make_unique<char[]>(rhs.size()+1);        
   len = rhs.size(); 
   strcpy(this->buffer.get(), rhs.buffer.get());
   return *this;
}

Str& Str::operator+=(const Str& rhs){
      size_t lhs_l = this->size();
      size_t rhs_l = rhs.size();
      std::unique_ptr<char []> temp = std::make_unique<char []>(lhs_l+rhs_l+1);
      strncat(temp.get(),this->buffer.get(),lhs_l);
      strncat(temp.get()+lhs_l, rhs.buffer.get(), rhs_l);
      buffer = move(temp);        
      len = lhs_l+rhs_l; 
      return *this;
}
