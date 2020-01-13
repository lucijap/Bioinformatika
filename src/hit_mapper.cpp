#include "hit_mapper.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> MapHits(vector<string>* hit_list,map<string,list<int>>* reference_kmers,int reference_size,int sequence_size,int k){
    int region_length = sequence_size;
    vector<int> hit_region_count;
    hit_region_count.reserve((unsigned int)(reference_size - region_length + 1));
    for (int i = 0; i < reference_size - region_length + 1; i++){
        hit_region_count[i] = 0;
    }

    // count number of hits per region
    for(auto const&hit:*hit_list){

        list<int> indices =((*reference_kmers).find(hit))->second;

        for(auto const&idx:indices){
            int start;
            int end;
            if (idx + k<region_length) {
                start = 0;
                end = idx + 1;
            } else if (idx > reference_size - region_length) {
                start = idx - region_length + k;
                end = min(idx + 1, reference_size - region_length + 1);
            } else {
                start=idx-region_length+k;
                end = idx+1;
            }
            for(int i=start;i<end;i++){
                hit_region_count[i]+=1;
            }
        }
    }


    // choose region with the most number of hits
    int max_hits = 0;
    int max_hits_region = 0;
    for (int i = 0; i < reference_size - region_length + 1; i++) {
        if (hit_region_count[i] > max_hits) {
            max_hits = hit_region_count[i];
            max_hits_region = i;
        }
    }

    int max_hitters = 0;

    for (int i = 0; i < reference_size - region_length + 1; i++) {
        if (hit_region_count[i] == max_hits) {
            max_hitters += 1;
        }
    }
    cout << "most hits: " << max_hits << endl;
    cout << "regions with most hits: " << max_hitters << endl;



    return make_pair(max_hits_region,region_length);
}