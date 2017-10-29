#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
    bool firstLoop = true;
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
            if(gotToken.GetTokenType() == T_SLASH)
            {
                if(slashFlag == true)
                {
                    inFile.ignore(256, '\n');
                    slashFlag = false;
                }
                slashFlag = true;
            }
            if(slashFlag && gotToken.GetTokenType() != T_SLASH)
            {
                slashFlag = false;
                if(vFlag)
                    cout << "T_SLASH" << endl;
                numToken++;
            }
            if(gotToken.GetTokenType() != T_SLASH)
                numToken++;
            if(vFlag && gotToken.GetTokenType() != T_SLASH)
                cout << gotToken << endl;
            if(gotToken.GetTokenType() == T_ID)
                numId++;
            if(gotToken.GetTokenType() == T_SCONST)
                numString++;
            if(sFlag && gotToken.GetTokenType() == T_SCONST)
                strings.push_back(gotToken.GetLexeme());
            if(iFlag && gotToken.GetTokenType() == T_ID)
                identifiers.push_back(gotToken.GetLexeme());
            gotToken = getToken(&inFile);
        }
    }
    else
    {
        while(getline(cin, input))
        {
            inString << " " << input;
        }
        gotToken = getToken(&inString);
        while (!(gotToken.GetTokenType() == T_DONE || gotToken.GetTokenType() == T_ERROR))
        {
            if(gotToken.GetTokenType() == T_SLASH)
            {
                if(slashFlag == true)
                {
                    inString.ignore(256, '\n');
                    slashFlag = false;
                }
                slashFlag = true;
            }
            if(slashFlag && gotToken.GetTokenType() != T_SLASH)
            {
                slashFlag = false;
                if(vFlag)
                    cout << "T_SLASH" << endl;
                numToken++;
            }
            if(gotToken.GetTokenType() != T_SLASH)
                numToken++;
            if(vFlag && gotToken.GetTokenType() != T_SLASH)
                cout << gotToken << endl;
            if(gotToken.GetTokenType() == T_ID)
                numId++;
            if(gotToken.GetTokenType() == T_SCONST)
                numString++;
            if(sFlag && gotToken.GetTokenType() == T_SCONST)
                strings.push_back(gotToken.GetLexeme());
            if(iFlag && gotToken.GetTokenType() == T_ID)
                identifiers.push_back(gotToken.GetLexeme());
            gotToken = getToken(&inString);
        }
    }
    if(gotToken.GetTokenType() == T_ERROR)
    {
        cout << "Lexical error " << gotToken << endl;
        return 0;
    }
    lineNumber = gotToken.GetLinenum();
    if(lineNumber < 1)
        lineNumber++;
    cout << "Token count: " << numToken << endl;
    cout << "Identifier count: " << numId << endl;
    cout << "String count: " << numString << endl;
    if(sFlag)
    {
        sort(strings.begin(), strings.end());
        firstLoop = true;
        for(vector<string>::iterator sit = strings.begin(); sit != strings.end(); ++sit)
        {
            if(firstLoop)
            {
                cout << *sit;
                firstLoop = false;
            }
            else
            {
                cout << ", ";
                cout << *sit;
            }
        }
        if(!strings.empty())
            cout << endl;
    }
    if(iFlag)
    {
        sort(identifiers.begin(), identifiers.end());
        firstLoop = true;
        for(vector<string>::iterator iit = identifiers.begin(); iit != identifiers.end(); ++iit)
        {
            if(firstLoop)
            {
                cout << *iit;
                firstLoop = false;
            }
            else
            {
                cout << ", ";
                cout << *iit;
            }
        }
        if(!identifiers.empty())
            cout << endl;
    }
    return 0;
}
