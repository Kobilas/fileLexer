#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "tokenizer.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    istringstream inString;
    bool sFlag = false;
    bool iFlag = false;
    bool vFlag = false;
    int fileCounter = 0;
    int index = -1;
    TokenType gotToken;
    for (int i = 0; i < argc; i++)
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
        if (!inFile.is_open())
        {
            cout << argv[index] << "FILE NOT FOUND";
            return 0;
        }
        gotToken = getToken(inFile);
        while (!(gotToken == T_DONE || gotToken == T_ERROR))
        {
            gotToken = getToken(inFile);
        }
    }
    else
    {
        inString << cin;
        gotToken = getToken(inString);
        while (!(gotToken == T_DONE || gotToken == T_ERROR))
        {
            gotToken = getToken(inString);
        }
    }
}