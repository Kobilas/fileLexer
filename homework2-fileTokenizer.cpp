#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "lexer.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    stringstream inString;
    string input = "";
    string buffer = "";
    bool sFlag = false;
    bool iFlag = false;
    bool vFlag = false;
    bool slashFlag = false;
    int fileCounter = 0;
    int index = -1;
    int numToken = 0;
    int numId = 0;
    int numString = 0;
    int lineNumber = 1;
    Token gotToken;
    vector<string> strings;
    vector<string> identifiers;
    for (int i = 1; i < argc; i++)
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
                cout << argv[i] << " INVALID FLAG" << endl;
                return 0;
            }
        }
        else
        {
            fileCounter++;
            index = i;
        }
    }
    if (fileCounter > 0)
    {
        if (fileCounter > 1)
        {
            cout << "TOO MANY FILES" << endl;
            return 0;
        }
        inFile.open(argv[index]);
        if (!inFile.is_open())
        {
            cout << argv[index] << " FILE NOT FOUND" << endl;
            return 0;
        }
        gotToken = getToken(&inFile);
        while (!(gotToken.GetTokenType() == T_DONE || gotToken.GetTokenType() == T_ERROR))
        {
            if (gotToken.GetTokenType() == T_SLASH)
            {
                if (slashFlag == true)
                {
                    inFile.ignore(256, '\n');
                    slashFlag = false;
                }
                slashFlag = true;
            }
            else
            {
                if (vFlag)
                    cout << "T_SLASH";
                slashFlag = false;
            }
            if (vFlag && gotToken.GetTokenType() != T_SLASH)
                cout << gotToken;
            if (gotToken.GetTokenType() == T_ID)
                numId++;
            if (gotToken.GetTokenType() == T_SCONST)
                numString++;
            if (sFlag)
                strings.push_back(gotToken.GetLexeme());
            if (iFlag)
                identifiers.push_back(gotToken.GetLexeme());
            gotToken = getToken(&inFile);
        }
    }
    else
    {
        cin >> input;
        inString << input;
        gotToken = getToken(&inString);
        while (!(gotToken.GetTokenType() == T_DONE || gotToken.GetTokenType() == T_ERROR))
        {
            if (gotToken.GetTokenType() == T_SLASH)
            {
                if (slashFlag == true)
                {
                    inFile.ignore(256, '\n');
                    slashFlag = false;
                }
                slashFlag = true;
            }
            else
            {
                if (vFlag)
                    cout << "T_SLASH";
                slashFlag = false;
            }
            if (vFlag && gotToken.GetTokenType() != T_SLASH)
                cout << gotToken;
            if (gotToken.GetTokenType() == T_ID)
                numId++;
            if (gotToken.GetTokenType() == T_SCONST)
                numString++;
            if (sFlag)
                strings.push_back(gotToken.GetLexeme());
            if (iFlag)
                identifiers.push_back(gotToken.GetLexeme());
            gotToken = getToken(&inString);
        }
    }
    if (gotToken.GetTokenType() == T_ERROR)
    {
        cout << "Lexical error " << gotToken << endl;
        return 0;
    }
    lineNumber = gotToken.GetLinenum();
    if (lineNumber < 1)
        lineNumber++;
    cout << "Token count: " << numToken << endl;
    cout << "Identifier count: " << numId << endl;
    cout << "String count: " << numString << endl;
    if (sFlag)
    {
        cout << "Strings: ";

    }
    if (iFlag)
    {
        cout << "Identifiers: ";
    }
    return 0;
}