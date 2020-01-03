#include "input_data_readers.h"
#include <string>
#include <list>
#include <fstream>
using namespace std;


string ReadReferentGenome(string path){

    string line;
    string referent_genome;
    ifstream file(path);

    if(file.is_open()){
        // skipping the header line
        getline(file,line);
        while(getline(file,line)){
            referent_genome+=line;
        }
        file.close();
    }
    return referent_genome;
}

list<string> ReadMutatedGenomeSequences(string path){

    string line;
    list<string> sequences;
    ifstream file(path);

    if(file.is_open()){
        // skipping header line
        getline(file,line);
        while(getline(file,line)){
            sequences.push_back(line);
            // skipping every other line (headers)
            getline(file,line);
        }
    }
    return sequences;
}
