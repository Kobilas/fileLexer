#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include "lexer.h"

using namespace std;

Token getToken(istream* br)
{
    map<string, TokenType> tknTypMap = {
        { "int", T_INT },
        { "string", T_STRING },
        { "set", T_SET },
        { "print", T_PRINT },
        { "println", T_PRINTLN },
        { "+", T_PLUS },
        { "-", T_MINUS },
        { "*", T_STAR },
        { "/", T_SLASH },
        { "(", T_LPAREN },
        { ")", T_RPAREN },
        { ";", T_SC }
    };
    string first = "";
    string comparison = "\"";
    first += br->get();
    br->putback(first[0]);
    string lexeme = "";
    bool numFlag = false;
    bool idFlag = false;
    bool stringFlag = false;
    if (isdigit(first))
        numFlag = true;
    else if (isalpha(first))
        idFlag = true;
    else if (comparison.compare(first) == 0)
        stringFlag = true;
    char c;
    while (!isspace(br->peek()))
    {
        c = br->get();
        if (numFlag && isdigit(c))
            lexeme += c;
        if (idFlag && isalnum(c))
            lexeme += c;
        if (stringFlag)
            lexeme += c;
    }
    return Token(T_ERROR, "");
}