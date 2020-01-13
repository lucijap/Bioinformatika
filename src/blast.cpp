#include "blast.h"
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void printAllKLengthRec(char set[], string prefix,list<string>*result ,int n, int k){

    if (k == 0)
    {
        result->push_back(prefix);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        string newPrefix;

        newPrefix = prefix + set[i];

        printAllKLengthRec(set, newPrefix,result, n, k - 1);
    }

}



vector<string> Blast(vector<string>* reference_kmers, map<string, list<int>>* seq_kmers,int k){

    // generate list of keys in reference_kmers

    // generate list of hits
    vector<string> seq_keys;
    for(auto const&k_mer:*seq_kmers){
        seq_keys.push_back(k_mer.first);
    }

    vector<string> hit_list;
    set_intersection(reference_kmers->begin(), reference_kmers->end(), seq_keys.begin(), seq_keys.end(), inserter(hit_list,  hit_list.begin()));
    return hit_list;
}

