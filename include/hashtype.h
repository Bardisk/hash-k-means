#ifndef _HASHTYPE_H_
#define _HASHTYPE_H_

using ULL = unsigned long long;

class hashtype
{
  unsigned long long value;
  public:
    hashtype(unsigned long long _value=0) :value(_value) {}
    operator unsigned long long() {
      return value;
    }
    unsigned long long get_value() {
      return value;
    }
    ULL operator - (const hashtype &b) const {
      return __builtin_popcountll(b.value ^ value);
    } 
    bool test(int bitnum) const {
      return value & (1ull << bitnum);
    }
    void flip(int bitnum) {
      value ^= (1ull << bitnum);
    }
    void set(int bitnum) {
      value |= (1ull << bitnum);
    }
    void reset(int bitnum) {
      value &= ~(1ull << bitnum);
    }
    hashtype operator + (const hashtype &b) const {
      return hashtype(value ^ b.value);
    }
};


#endif