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
#include <set>
#include <ctime>

using namespace std;


int main(int argc, char *argv[]) {

    //parse arguments

    string reference_path = argv[1];
    string mutated_path = argv[2];
    int w = atoi(argv[3]);
    int k = atoi(argv[4]);

    clock_t begin = clock();


    string reference = ReadReferentGenome(reference_path);
    list<string> sequences = ReadMutatedGenomeSequences(mutated_path);


    // generating k-mers for reference
    map<string, list<int>> kmers = GenerateKmers(&reference, w, k);


    // get vector of k-mers without index lists
    vector<string> keys;
    keys.reserve(kmers.size());
    for(auto const&itt:kmers){
        keys.push_back(itt.first);
    }

    sort(keys.begin(), keys.end());

    vector<unsigned int> mutation_list;
    map<unsigned int, short> counters;
    pair<int,int> region;
    map<string, list<int>> seq_kmers;
    vector<string> hit_list;

    // detecting mutations
    cout << "start" << endl;
    int i = 0;
    for (auto const& it :sequences) {
        i++;
        if (i%10==0){
            cout << 100 * i / sequences.size() << endl;
        }
        string sequence = it;

        // generate k-mers of read sequence
        seq_kmers = GenerateKmers(&sequence, w, k);

        // generates hit_list of k-mers
        hit_list = Blast(&keys, &seq_kmers, k);


        seq_kmers.erase(seq_kmers.begin(), seq_kmers.end());

        // finds mapping regions
        region = MapHits(&hit_list, &kmers, reference.size(), sequence.size(), k);
        if (region.second==0){
            continue;
        }

        hit_list.clear();
        string hit_region = reference.substr(region.first, region.second);

        // local alignment with Smith Waterman and writing mutations to csv file
        mutation_list = SmithWaterman(hit_region, sequence, region.first);
        for(auto const&mutation:mutation_list){
            counters[mutation] += 1;
        }




    }
    cout << "end" << endl;

    // open result file
    ofstream outfile ("../our_mutated.csv");
    int counter;
    int max_size = (int) reference.size() - 4000;

    vector<unsigned int> cnt_keys;
    cnt_keys.reserve(counters.size());
    for(auto const&itt:counters){
        cnt_keys.push_back(itt.first);
    }

    unsigned int position;
    unsigned int letter_hash;
    unsigned int type_hash;
    unsigned int first_two;
    char type = 'N';
    char letter = 'N';
    for(auto &mutation:cnt_keys){
        first_two = mutation/100000000;
        position = mutation - first_two * 100000000;
        type_hash = first_two/10;
        switch(type_hash) {
            case 0:
                type = 'X';
                break;
            case 1:
                type = 'D';
                break;
            case 2:
                type = 'I';
                break;
            default:
                break;
        }

        letter_hash = first_two % 10;

        switch(letter_hash) {
            case 0:
                letter = '-';
                break;
            case 1:
                letter = 'A';
                break;
            case 2:
                letter = 'C';
                break;
            case 3:
                letter = 'G';
                break;
            case 4:
                letter = 'T';
                break;
            default:
                break;
        }


        if (position<4000 || position>max_size){
            if(counters[mutation]>=4){
                outfile << type << "," << position << "," << letter << endl;
            }
        }else {
            if (counters[mutation] >= 10) {
                outfile << type << "," << position << "," << letter << endl;
            }
        }

    }
    outfile.close();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Time elapsed: "<<elapsed_secs<<" s"<<endl;
}
