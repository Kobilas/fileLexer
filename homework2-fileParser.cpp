#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "lexer.h"

using namespcae std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    bool sFlag = false;
    bool iFlag = false;
    bool vFlag = false;
    bool manyInFlag = false;
    bool invalidFlag = false;
    int fileCounter = 0;
    int index = -1;
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
                invalidFlag = true;
                cout << argv[i] << "INVALID FLAG" << endl;
                break;
            }
        }
        else
        {
            fileCounter++;
            index = i;
        }
            if (fileCounter > 1)
        {
            manyInFlag = true;
            cout << "TOO MANY FILES" << endl;
            break;
        }
        if (invalidFlag)
            break;
    }
    if (manyInFlag)
        return 0;
    if (invalidFlag)
        return 0;
    
}

extern Token getToken(*istream br)
{
    
}