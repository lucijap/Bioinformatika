#include <string>
#include <list>
#include <vector>
using namespace std;
#ifndef SRC_SMITH_WATERMAN_H
#define SRC_SMITH_WATERMAN_H

//
// Created by Ivan Ištuk and Marko Meštrović.
//

/**
 * Implements the Smith Waterman algorithm, which gives us the best local alignment for the two given sequences.
 *
 * @param sequence_A: hit_region which is used to gain the mutations from the sequence
 * @param sequence_B: sequence where the mutations are being looked for
 * @param region_start: index of the region start
 * @return list of mutations as a tuple of <char, int, char>
 */
vector<unsigned int> SmithWaterman(string sequence_A, string sequence_B, int region_start);

#endif //SRC_SMITH_WATERMAN_H
