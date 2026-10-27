#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class IO
{
public:
    IO();
    ~IO();

    int convertStringToInt(string);
    double convertStringToDouble(string);
    char *convertStringToChar(string);

    vector<string> readFileLine(string); 
    vector<string> parseLine(string);    

    void write(string filename, vector<string> content); 
};

#endif