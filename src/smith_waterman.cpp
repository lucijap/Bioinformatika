#include "smith_waterman.h"
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

short SimilarityScore(char a, char b) {
  if (a == b) {
      return (short) 3;
  } else {
      return (short) -5;
  }
}
bool sortbysec(const tuple<int, int, int>& a,
               const tuple<int, int, int>& b)
{
    return (get<1>(a) < get<1>(b));
}


pair<string, string> SmithWaterman(string sequence_A, string sequence_B, int region_start) {
    int dim_A = sequence_A.length();
    int dim_B = sequence_B.length();
    const short penalty = 4;

    map<pair<short, short>, pair<short, short>> traceback;
    short last_line[dim_B + 1];
    short current_line[dim_B + 1];
    for (int i = 0; i < dim_B + 1; i++) {
        last_line[i] = 0;
    }

    int match = 0, insertion = 0, deletion = 0, maximum_value = 0;
    int max_so_far = 0;
    pair<int, int> max_pair;
    for (int i = 1; i < dim_A + 1; i++) {
        current_line[0] = 0;
        for (int j = 1; j < dim_B + 1; j++) {
            match = last_line[j - 1] + SimilarityScore(sequence_A[i - 1], sequence_B[j - 1]);
            insertion = current_line[j - 1] - penalty;
            deletion = last_line[j] - penalty;
            maximum_value = max({0, match, insertion, deletion});
            current_line[j] = (short) maximum_value;
            if (maximum_value != 0) {
                if (maximum_value == match) {
                    traceback.insert({pair<int, int>(i, j), pair<int, int>(i - 1, j - 1)});
                } else if (maximum_value == insertion) {
                    traceback.insert({pair<int, int>(i, j), pair<int, int>(i, j - 1)});
                } else if (maximum_value == deletion) {
                    traceback.insert({pair<int, int>(i, j), pair<int, int>(i - 1, j)});
                }
                if (maximum_value > max_so_far) {
                    max_so_far = maximum_value;
                    max_pair = pair<int, int> (i, j);
                }
            }
        }
        for (int k = 0; k < dim_B + 1; k++) {
            last_line[k] = current_line[k];
        }
    }
    ofstream outfile ("ecoli_mutated_test.csv");
    string first;
    string second;
    list<tuple<char,int,char>> list_of_mutations;
    tuple<char,int,char> mutation_tuple;
    int sum;
    char mutation_char;
    char char_of_second;
    while (traceback.count(max_pair)) {
        pair<int, int> next_pair = traceback.at(max_pair);
        if (next_pair.first == max_pair.first - 1 and next_pair.second == max_pair.second - 1) {
            if (sequence_A[next_pair.first] != sequence_B[next_pair.second]){
                mutation_char ='X';
                sum=next_pair.first+region_start;
                char_of_second=sequence_B[next_pair.second];
                mutation_tuple = make_tuple(mutation_char,sum, char_of_second);
                list_of_mutations.push_back(mutation_tuple);
                //cout << next_pair.first + region_start << endl; //mutacija mijenjanje
            }
            //first += sequence_A[next_pair.first];
            //second += sequence_B[next_pair.second];
        } else if (next_pair.first == max_pair.first - 1 and next_pair.second == max_pair.second) {
            //first += sequence_A[next_pair.first];
            //second += "-";
            //cout << next_pair.first + region_start << endl;// umetanje
            mutation_char ='D';
            sum=next_pair.first+region_start;
            char_of_second=sequence_A[next_pair.first];
            mutation_tuple = make_tuple(mutation_char,sum, char_of_second);
            list_of_mutations.push_back(mutation_tuple);
        } else if (next_pair.first == max_pair.first and next_pair.second == max_pair.second - 1) {
            //first += "-";
            //second += sequence_B[next_pair.second];
            mutation_char ='I';
            sum=next_pair.first+region_start;
            char_of_second=sequence_B[next_pair.second];
            mutation_tuple = make_tuple(mutation_char,sum, char_of_second);
            list_of_mutations.push_back(mutation_tuple);
            //cout << next_pair.first + region_start << endl;//brisanje
        }
        max_pair = next_pair;
    }

    list_of_mutations.reverse();
//    sort(list_of_mutations.begin(), list_of_mutations.end(), sortbysec);
    for(auto const&mutation:list_of_mutations){
        outfile << get<0>(mutation) << "," << get<1>(mutation) << "," <<get<2>(mutation)<<endl;
    }
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    outfile.close();
    /*
    cout << first << endl;
    cout << second << endl;

    cout << "\t\t";
    for (int i = 0; i < dim_B; i++) {
        cout << sequence_B[i] << "\t";
    }

    cout << endl;

    for (int i = 0; i < dim_A + 1; i++) {
        if (i > 0) {
            cout << sequence_A[i - 1] << "\t";
        } else {
            cout << "\t";
        }
        for (int j = 0; j < dim_B + 1; j++) {
            cout << scoring_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    */
    return pair<string, string> (first, second);

}
