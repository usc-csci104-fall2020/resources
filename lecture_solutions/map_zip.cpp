// map_zip.cpp - Mark Redekopp
//
// Another example usage of maps:  sparse arrays
//  A sparse array is one where only a few indicides
//  are used but the range of index values is large

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm> // needed for built-in sort
using namespace std;

bool zip_comp(const pair<int,int> &lhs, const pair<int,int> &rhs)
{ return lhs.first < rhs.first; }
bool occ_comp(const pair<int,int> &lhs, const pair<int,int> &rhs)
{ return lhs.second < rhs.second; }

int main(int argc, char *argv[])
{
  if(argc < 2){
    cerr << "Usage: ./map_zip zipcode_filename" << endl;
    return -1;
  }
  ifstream zipfile(argv[1]);
  if(!zipfile.good()){
    cerr << "Unable to open file" << argv[1] << endl;
  }
  vector<int> all_zips;

  int zipCode;
  zipfile >> zipCode;
  while(!zipfile.fail()){
    all_zips.push_back(zipCode);
    zipfile >> zipCode;
  }
  zipfile.close();

  // Key = zipcode, Value = Num. of Occurrences
  // Iterate through all the zip codes in 'all_zips' and 
  // create a map of zipcode to number of occurrences
 
   map<int,int> zip_map;
   vector<int>::iterator it;
   map<int,int>::iterator map_it;
   
  for(it = all_zips.begin(); it != all_zips.end(); it++)
  {
      map_it = zip_map.find(*it);
      if (map_it == zip_map.end()){
         zip_map[*it] = 1;
      } else {
         map_it->second++;
      }
          
   }
