#include <string>
#include <list>

#ifndef MUTATIONDETECTION_INPUT_DATA_READERS_H
#define MUTATIONDETECTION_INPUT_DATA_READERS_H

#endif //MUTATIONDETECTION_INPUT_DATA_READERS_H

using namespace std;

//
// Created by Lucija Planinić.
//

/**
 * Reads data from the file containing the referent genome.
 * @param path: path to file containing referent genome
 * @return string containing the referent genome
 */
string ReadReferentGenome(string path);

//
// Created by Lucija Planinić.
//

/**
 * Reads data from the file containing mutated genome reads.
 * @param path: path to file containing mutated genome reads
 * @return  string containing the mutated genome
 */
list<string> ReadMutatedGenomeSequences(string path);