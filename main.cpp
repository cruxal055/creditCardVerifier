#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

void grabData(char arr[], int sizeofarr, istream &file);
void trash(istream &file, int spacesOfTrash);
void save(ofstream &newFile, char arr[], int size, char var);


int main()
{
    return 0;
}
void trash(istream &file, int spacesOfTrash)
{
    char junk;
    for(size_t i = 0; i< spacesOfTrash;++i)
        file.get(junk);
}
void grabData(char arr[], int sizeofarr, istream &file)
{
    for(size_t i = 0; i < sizeofarr; ++i)
        file.get(arr[i]);
}
void save(ofstream &newFile, char arr[], int size, char var)
{
    for(size_t i = 0; i < size; ++i)
        newFile << arr[i];
    newFile << var;
}
