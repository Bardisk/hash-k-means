#ifndef _DATA_H_
#define _DATA_H_

#include <map>
#include <hashtype.h>
#include <vector>

extern std::map<unsigned long long, int> muls;
extern hashtype centers[];
extern hashtype samples[];
extern int representor[];
extern int sample_cnt, center_cnt;
extern std::vector <int> members[];
extern int overall_sample_cnt;
#endif