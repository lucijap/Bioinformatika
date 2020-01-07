#include <string>
#include <map>
#include <list>
#include <iostream>
using namespace std;

#ifndef MUTATIONDETECTION_BLAST_H
#define MUTATIONDETECTION_BLAST_H

#endif //MUTATIONDETECTION_BLAST_H

map<std::pair<char,char>,int> blosum62={{make_pair('A','A'),4},{make_pair('A','C'),0},{make_pair('A','G'),0},{make_pair('A','T'),0},{make_pair('A','-'),-4},
                                        {make_pair('C','A'),0},{make_pair('C','C'),9},{make_pair('C','G'),-3},{make_pair('C','T'),-1},{make_pair('C','-'),-4},
                                        {make_pair('G','A'),0},{make_pair('G','C'),-3},{make_pair('G','G'),6},{make_pair('G','T'),-2},{make_pair('G','-'),-4},
                                        {make_pair('T','A'),0},{make_pair('T','C'),-1},{make_pair('T','G'),-2},{make_pair('T','T'),5},{make_pair('T','-'),-4},
                                        {make_pair('-','A'),-4},{make_pair('-','C'),-4},{make_pair('-','G'),-4},{make_pair('-','T'),-4},{make_pair('-','-'),1}};

list<string> Blast(map<string,list<int>> reference_kmers, string sequence, int k);