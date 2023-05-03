#include <getopt.h>
#include <random>
#include <ctime>
#include <preprocessor.h>
#include <data.h>
#include <procedure.h>
#include <array>
#include <cassert>

#define MAX_CLSTR 65536
#define MAX_SAMPLE 1048576

hashtype centers[MAX_CLSTR];
hashtype samples[MAX_SAMPLE];
int representor[MAX_SAMPLE] = {0};
std::vector <int> members[MAX_CLSTR];
int sample_cnt = 0, center_cnt;

std::set <ULL> center_set;
int min_dist[MAX_SAMPLE];

int main(int argc, char *argv[]) {
  int opt, t = 3;
  while (~(opt = getopt(argc, argv, "c:t:"))) {
    switch (opt)
    {
      case 'c':
        sscanf(optarg, "%d", &center_cnt);
        break;
      case 't':
        sscanf(optarg, "%d", &t);
        break;
      default:
        return -1;
    }
  }

  preprocessor();
  for (auto item : muls) {
    samples[sample_cnt++] = hashtype(item.first);
  }
  fprintf(stderr, "all sample count: %d\n", overall_sample_cnt);
  fprintf(stderr, "sample count: %d\n", sample_cnt);

  std::default_random_engine generator(std::time(nullptr));
  std::uniform_int_distribution<int> random_sample_num(0, sample_cnt - 1);
  std::uniform_int_distribution<int> random_center_num(0, center_cnt - 1);

  //select initial center
  centers[0] = samples[random_sample_num(generator)];
  for (int sample = 0; sample < sample_cnt; sample++) min_dist[sample] = (centers[0] - samples[sample]) * (centers[0] - samples[sample]) * muls[samples[sample]];
  center_set.insert(centers[0]);
  fprintf(stderr, "initial center %016llx\n", centers[0].get_value());

  //kmeans++
  for (int i = 1; i < center_cnt; i++) {
initial:
    //choose a new center by weighted distribution D(x)^2
    std::discrete_distribution<int> weighted_random_sample(min_dist, min_dist + sample_cnt);
    int chosen_center = weighted_random_sample(generator);
    
    //if it is duplicate, restart
    //should not happen actually
    if (center_set.find(samples[chosen_center]) != center_set.end()) {
      fprintf(stderr, "In round %d, choose %016llx\n", i, samples[chosen_center].get_value());
      fprintf(stderr, "center number %d min_dist %d representer %d\n", chosen_center, min_dist[chosen_center], representor[chosen_center]);
      assert(0);
      goto initial;
    }
    else center_set.insert(samples[chosen_center]);

#ifdef DB
    fprintf(stderr, "In round %d, choose %016llx\n", i, samples[chosen_center].get_value());
#endif
    centers[i] = samples[chosen_center];

    //update representor and min_dist
    for (int sample = 0; sample < sample_cnt; sample++) {  
      if (centers[i] - samples[sample] < centers[representor[sample]] - samples[sample]) {
        representor[sample] = i;
        min_dist[sample] = (centers[i] - samples[sample]) * (centers[i] - samples[sample]) * muls[samples[sample]];
#ifdef DB
        fprintf(stderr, "%016llx %016llx %llu\n", centers[i].get_value(), samples[sample].get_value(), centers[i] - samples[sample]);
#endif
      }
    }
  }

  fprintf(stderr, "Initialization Completed!\n");
  set_members();

  while(t--) {
    for (int i = 0; i < center_cnt; i++) center_nxt(i);
    for (int i = 0; i < sample_cnt; i++) get_representor(i);
    set_members();
    if (report() == 0) break;
  }

  dumpans();

  return 0;
}