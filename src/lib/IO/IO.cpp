#include "IO/IO.hpp"
#include <sstream>

IO::IO() {}
IO::~IO() {}

int IO::convertStringToInt(string str)
{
    try
    {
        return stoi(str);
    }
    catch (...)
    {
        cerr << "Gagal konversi ke int: " << str << endl;
        return 0;
    }
}

double IO::convertStringToDouble(string str)
{
    try
    {
        return stod(str);
    }
    catch (...)
    {
        cerr << "Gagal konversi ke double: " << str << endl;
        return 0.0;
    }
}

char *IO::convertStringToChar(string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

vector<string> IO::readFileLine(string filename)
{
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file: " << filename << endl;
        return lines;
    }

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

vector<string> IO::parseLine(string line)
{
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word)
    {
        words.push_back(word);
    }
    return words;
}

void IO::write(string filename, vector<string> content)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file: " << filename << " untuk ditulis.\n";
        return;
    }

    for (const auto& line : content)
    {
        file << line << "\n";
    }

    file.close();
}