#include <string>
#include <map>
#include <list>
#include <iostream>
#include <set>

using namespace std;

#ifndef SRC_MINIMAP_H
#define SRC_MINIMAP_H


unsigned int InvertibleHash(unsigned int x, int p);
set<tuple<int, int, int>> MinimizerSketch(string* s, int w, int k);
unsigned int KmerHash(string s, int k);
int NucleotideHash(char N);
string SequenceComplement(string* s);

#endif //SRC_MINIMAP_H
