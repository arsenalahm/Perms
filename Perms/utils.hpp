#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <map>
#include <iostream>

using namespace std;

struct node {
    int num;
    // direction = 0 means left and 1 means right
    int direction;
};

int count_smaller_right(int data[], int begin, int end, int target);
map<int, int> get_middle(int data[], int size);
// stride = 1 for incresedDecimal and -1 for decreasedDecimal
void add(int size, map<int, int>& middle, int index, int stride, bool lexi = false);
void transfer(int data[], int size, map<int, int> middle);

// for 0,1,...,(n-1)
long long get_rank(int data[], int size);
void gen_perm(long long rank, int size, int data[]);

#endif /* utils_hpp */
