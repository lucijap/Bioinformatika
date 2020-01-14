#include <iostream>
#include "input_data_readers.h"
#include <string>
#include <list>
#include "smith_waterman.h"
#include "k_mer_generator.h"
#include "blast.h"
#include "hit_mapper.h"
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    ofstream outfile ("lambda_mutated_test.csv");
    int w = 5;
    int k = 11;
    string reference = ReadReferentGenome("../train-data/lambda.fasta");
    list<string> sequences = ReadMutatedGenomeSequences("../train-data/lambda_simulated_reads.fasta");


    //set<tuple<int, int, int>> result = MinimizerSketch(&reference, w, k);

    //cout << "done with read" << endl;
    map<string, list<int>> kmers = GenerateKmers(&reference, w, k);

    //cout << "done with gen kmers" << endl;

    //auto it = sequences.begin();
    //advance(it,1);
    //string sequence = *it;


    vector<string> keys;
    keys.reserve(kmers.size());
    for(auto const&itt:kmers){
        keys.push_back(itt.first);
    }

    sort(keys.begin(), keys.end());

    list<tuple<char,int,char>> mutation_list;
    list<tuple<char,int,char>> result;
    int i = 0;
    for (auto it :sequences) {
        string sequence = it;
        map<string, list<int>> seq_kmers = GenerateKmers(&sequence, w, k);
        vector<string> hit_list = Blast(&keys, &seq_kmers, k);
        //cout << "done with hit list" << endl;
        seq_kmers.erase(seq_kmers.begin(), seq_kmers.end());
        pair<int,int> region = MapHits(&hit_list, &kmers, reference.size(), sequence.size(), k);
        if (region.second==0){
            continue;
        }
        //cout << "done with map hit" << endl;

        hit_list.clear();
        string hit_region = reference.substr(region.first, region.second);
        result = SmithWaterman(hit_region, sequence, region.first);
        //cout << "done with smith" << endl;
        i++;
        if (i%10==0){
            cout<<"--------------------------"<<i<<"---------------------"<<endl;
        }

        /*for(auto const &element: result){
            mutation_list.push_back(element);
        }*/
    }
    /*or(auto const&mutation:mutation_list){
        cout <<get<0>(mutation) << "," << get<1>(mutation) << "," <<get<2>(mutation)<<endl;
        outfile << get<0>(mutation) << "," << get<1>(mutation) << "," <<get<2>(mutation)<<endl;
    }

    outfile.close();


    /*std::sort(begin(mutation_list), end(mutation_list),
              [](tuple<char, int, char> const &t1, tuple<char, int, char> const &t2) {
                  return get<1>(t1) < get<1>(t2); // or use a custom compare function
              }
    );*/
    /*sort(mutation_list.begin(),mutation_list.end(),
         [](const tuple<char,int,char>& a,
            const tuple<char,int,char>& b) -> bool
         {
             return get<1>(a) > get<1>(b);
         });
    for(auto const&mutation:mutation_list){
        outfile << get<0>(mutation) << "," << get<1>(mutation) << "," <<get<2>(mutation)<<endl;
    }
    outfile.close();





    /*
    for(auto elem : words) {
        cout << elem.first << endl;
        for (auto el2 : elem.second) {
            cout << el2 + 1 << " ";
        }
        cout << endl;
    }

    pair<string, string> sequences = SmithWaterman("GGTTGACTA", "TGTTACGG");
    cout << sequences.first << endl;
    cout << sequences.second << endl;

    char sequence[12] = "GGTTGGTACTA";

    map<string,list<int>> words = GenerateKmers(sequence, 0, 3);
    for(auto elem : words) {
        cout << elem.first << endl;
        for (auto el2 : elem.second) {
            cout << el2 << " ";
        }
        cout << endl;
    }
    cout << ReadReferentGenome("../train-data/ecoli.fasta") << endl;
    list<string> sequences = ReadMutatedGenomeSequences("../train-data/ecoli_simulated_reads.fasta");
    list<string>::iterator it;
    int i=1;
    for(it=sequences.begin();it!=sequences.end();it++){
        cout << i <<". "<< *it << endl;
        i++;
    }

    return 0;
     */
}