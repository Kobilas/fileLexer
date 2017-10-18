#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include "lexer.h"

using namespace std;

Token getToken(istream* br)
{
    map<string,TokenType> tknTypMap = {
        {"int", T_INT},
        {"string", T_STRING},
        {"set", T_SET},
        {"print", T_PRINT},
        {"println", T_PRINTLN},
        {"+", T_PLUS},
        {"-", T_MINUS},
        {"*", T_STAR},
        {"/", T_SLASH},
        {"(", T_LPAREN},
        {")", T_RPAREN},
        {";", T_SC}
    };
    string lexeme = "";
    boolean numFlag = false;
    boolean idFlag = false;
    boolean stringFlag = false;
    if(isdigit(br->peek()))
        numFlag = true;
    else if(isalpha(br->peek())))
        idFlag = true;
    else if((br->peek()).compare("\"") == 0)
        stringFlag = true;
    while(!isspace(br->peek()))
    {
        if(numFlag && isdigit(br->peek()))
            lexeme += br->get();
        if(idFlag && isalnum(br->peek()))
            lexeme += br->get();
        if(stringFlag)
            lexeme += br->get();
    }
    return Token(T_ERROR, "");
}