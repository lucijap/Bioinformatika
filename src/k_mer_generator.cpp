#include "k_mer_generator.h"
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

string SequenceComplement(string* s) {
    string complement;
    for (char& c : *s) {
        switch (c) {
            case 'A':
                complement += "T";
                break;
            case 'C':
                complement += "G";
                break;
            case 'G':
                complement += "C";
                break;
            case 'T':
                complement += "A";
                break;
            default:
                throw invalid_argument("Non nucleotide letter encountered");
        }
    }
    reverse(complement.begin(), complement.end());
    return complement;
}

string map_for_ordering(string sequence, map<char, char> even, map<char, char> odd) {
    string s, sc;
    string complement = SequenceComplement(&sequence);

    for (int i = 0; i < sequence.size(); i++) {
        if (i % 2 == 0) {
            s += even[sequence.at(i)];
            sc += even[complement.at(i)];
        } else {
            s += odd[sequence.at(i)];
            sc += odd[complement.at(i)];
        }
    }

    if (s < sc) {
        return s;
    } else {
        return sc;
    }
}

map<string,list<int>> GenerateKmers(string* sequence,int w, int k){

    map<string,list<int>> k_mers;
    list<string> current_window;
    list<string>::iterator min_kmer_iter;
    string min_kmer;
    map<char, char> even = {{'C', '0'}, {'A', '1'}, {'T', '2'}, {'G', '3'}};
    map<char, char> odd = {{'G', '0'}, {'T', '1'}, {'A', '2'}, {'C', '3'}};

    // fill first window
    for(int i=0;i<w;i++){
        current_window.push_back(map_for_ordering(sequence->substr(i,k), even, odd));
    }



    // slide window along sequence
    for(int i=w;i<sequence->size() - 1;i++){
        if(i!=w){
            current_window.pop_front();
            current_window.push_back(map_for_ordering(sequence->substr(i - 1,k), even, odd));
        }

        // find minimal k-mer in current window and add it to k_mers
        min_kmer_iter = min_element(current_window.begin(),current_window.end());
        if(min_kmer != *min_kmer_iter ){
            if(k_mers.count(*min_kmer_iter)==0){
                k_mers.insert(pair<string,list<int>>(*min_kmer_iter,{i-w+distance(current_window.begin(), min_kmer_iter)}));
            }else{
                auto iter = k_mers.find(*min_kmer_iter);
                (*iter).second.push_back(i-w+distance(current_window.begin(), min_kmer_iter));
            }
            min_kmer = *min_kmer_iter;
        }
    }
    return k_mers;
}

