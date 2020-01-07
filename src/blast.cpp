#include "blast.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
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

list<string> getAllKLength(char set[], int k,int n){
    list<string> result;
    printAllKLengthRec(set, "", &result,n, k);
    return result;
}

list<string> Blast(map<string,list<int>> reference_kmers,string sequence,int k){

    int thresh = 5;
    char bases [4]= {'A','C','G','T'};
    list<string> all_kmers = getAllKLength(bases,k,4);
    list<string> kmers_to_compare;

    for(unsigned int i=0;i<sequence.size()-k;i++){
        string k_mer=sequence.substr(i,(unsigned int)k);

        for(auto const&k_mer1:all_kmers){
            int sum = 0;
            for(unsigned int j=0;j<k;j++){
                sum+=blosum62[make_pair(k_mer.at(j),k_mer1.at(j))];
            }
            if (sum>=thresh){
                kmers_to_compare.push_back(k_mer1);
            }
        }
    }

    list<string> hit_list;

    // generate list of keys in reference_kmers
    vector<string> keys;
    keys.reserve(reference_kmers.size());
    for(auto const&it:reference_kmers){
        keys.push_back(it.first);
    }

    // generate list of hits
    for(auto const&k_mer:kmers_to_compare){
        if(count(keys.begin(),keys.end(),k_mer)>0){
            hit_list.push_back(k_mer);
        }
    }

    return hit_list;
}

