#include <preprocessor.h>

std::map<unsigned long long, int> muls;
int overall_sample_cnt = 0;
void preprocessor() {
  unsigned long long x;
  while (~scanf("%llx", &x)) {
    overall_sample_cnt++;
    if (muls.find(x) == muls.end())
      muls[x] = 1;
    else muls[x]++;
  }
  return ;
}