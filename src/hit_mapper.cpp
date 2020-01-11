#include "hit_mapper.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> MapHits(list<string>* hit_list,map<string,list<int>>* reference_kmers,int reference_size,int sequence_size,int k){

    int region_length = sequence_size;
    vector<int> hit_region_count;
    hit_region_count.reserve((unsigned int)(reference_size));

    // count number of hits per region
    for(auto const&hit:*hit_list){

        list<int> indices =((*reference_kmers).find(hit))->second;

        for(auto const&idx:indices){
            int start;
            int end;
            if (idx<region_length) {
                start = 0;
                end = idx + 1;
            } else if(idx==sequence_size-1) {
                start = idx-region_length+1;
                end=idx;

            } else{
                start=idx-region_length+1;
                end = idx+1;
            }
            for(int i=start;i<end;i++){
                hit_region_count[i]+=1;
            }
        }
    }

    // choose region with the most number of hits

    for (auto el2 : hit_region_count) {
        cout << el2 << endl;
    }

    int max_hits_region = max_element(hit_region_count.begin(),hit_region_count.end())-hit_region_count.begin();

    return make_pair(max_hits_region*region_length,(max_hits_region+1)*region_length);
}