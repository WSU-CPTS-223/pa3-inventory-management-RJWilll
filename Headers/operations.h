#ifndef OP
#define OP

#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <algorithm>
#include "entry.h"
#include "hash.h"
#include "avl_map.h"

using namespace std;

void parseFile(hashTable<string, entry*>& h, avl_map<string, vector<entry*>>& map);

void Pause();

void relieveHeap(hashTable<string, entry*>& h);



#endif //OP