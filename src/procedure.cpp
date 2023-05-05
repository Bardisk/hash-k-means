#include <data.h>
#include <cstdio>

static long long inertia() {
  long long result = 0;
  for (int i = 0; i < sample_cnt; i++) {
    result += (samples[i] - centers[representor[i]]) * muls[samples[i]];
  }
  return result;
}

static long long SSE() {
  long long result = 0;
  for (int i = 0; i < sample_cnt; i++) {
    result += (samples[i] - centers[representor[i]]) * (samples[i] - centers[representor[i]]) * muls[samples[i]];
  }
  return result;
}

void center_nxt(int center) {
  hashtype res(0);
  for (int i = 0; i < 64; i++) {
    int cnt = 0;
    for (auto member : members[center]) {
      if (samples[member].test(i)) cnt += muls[samples[member]];
      else cnt -= muls[samples[member]];
    }
    if (cnt > 0) res.set(i);
  }
  centers[center] = res;
  members[center].clear();
}

void get_representor(int sample) {
  for (int i = 0; i < center_cnt; i++) {
    if (centers[i] - samples[sample] < centers[representor[sample]] - samples[sample]) {
      representor[sample] = i;
    }
  }
}

void set_members() {
  for (int i = 0; i < sample_cnt; i++)
    members[representor[i]].push_back(i);
}


long long report() {
  static long long prev_result = -1;
  long long now_res = inertia();
  fprintf(stderr, "inertia: %lld\n", now_res);
  fprintf(stderr, "SSE: %lld\n", SSE());
  if (!~prev_result) {
    prev_result = now_res;
    return __LONG_LONG_MAX__;
  }
  else {
    long long increment = prev_result - now_res;
    prev_result = now_res;
    return increment;
  }
}

void dumpans() {
  printf("%d\n", overall_sample_cnt);
  for (int i = 0; i < center_cnt; i++) {
    int cnt = 0;
    for (auto member : members[i])
      cnt += muls[samples[member]];
    printf("%04x %016llx %d\n", i, centers[i].get_value(), cnt);
  }
}