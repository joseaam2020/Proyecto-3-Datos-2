
#ifndef PROYECTO3_DISKSEARCHER_H
#define PROYECTO3_DISKSEARCHER_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <array>

using namespace std;

class DiskSearcher {
public:
    vector<string> libros;
    vector<string> diskpaths;
    vector<vector<string>> Bnames;
    vector<string> metaD;


    DiskSearcher();
    void find(string input);
    void insertdiskpath(vector<string> paths);
    vector<string> extractbookpaths(string path);
    void getBookNames(vector<string> paths, string del);
    vector<string> split(string input, string del);
    void book_to_meta();

};


#endif //PROYECTO3_DISKSEARCHER_H
