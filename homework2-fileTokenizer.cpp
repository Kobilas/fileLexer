#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "lexer.h"
#include "tokenizer.cpp"

using namespcae std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    bool sFlag = false;
    bool iFlag = false;
    bool vFlag = false;
    int fileCounter = 0;
    int index = -1;
    Tokenizer::Tokenizer
    for(int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 's':
                sFlag = true;
                break;
            case 'i':
                iFlag = true;
                break;
            case 'v':
                vFlag = true;
                break;
            default:
                cout << argv[i] << "INVALID FLAG" << endl;
                return 0;
            }
        }
        else
        {
            fileCounter++;
            index = i;
        }
        if (fileCounter > 1)
        {
            cout << "TOO MANY FILES" << endl;
            return 0;
        }
    }
    if (fileCounter == 1)
    {
        inFile.open(index);
        if(!inFile.is_open())
        {
            cout << argv[index] << "FILE NOT FOUND"
            return 0;
        }
        
    }
}