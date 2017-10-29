#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include "lexer.h"

using namespace std;

extern Token getToken(istream* br)
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
    char c;
    string lexeme = "";
    bool numFlag = false;
    bool idFlag = false;
    bool stringFlag = false;
    bool firstFlag = true;
    int lineNumber = 1;
    while ((c = br->get()))
    {
        if(c == '\n')
        {
            lineNumber++;
            if(stringFlag)
            {
                lexeme += c;
                return Token(T_ERROR, lexeme);
            }
        }
        if(firstFlag)
        {
            if(isspace(c))
                continue;
            switch (c){
                case '+':
                    return Token(T_PLUS, "");
                case '-':
                    return Token(T_MINUS, "");
                case '*':
                    return Token(T_STAR, "");
                case '/':
                    return Token(T_SLASH, "");
                case '(':
                    return Token(T_LPAREN, "");
                case ')':
                    return Token(T_RPAREN, "");
                case ';':
                    return Token(T_SC, "");
                default:
                    break;
            }
            if(c == '\"')
            {
                stringFlag = true;
                lexeme += c;
                firstFlag = false;
                continue;
            }
            if(isalpha(c))
                idFlag = true;
            if(isdigit(c))
                numFlag = true;
            firstFlag = false;
        }
        if (numFlag && isdigit(c))
            lexeme += c;
        else if (numFlag)
        {
            br->putback(c);
            return Token(T_ICONST, lexeme);
        }
        if (idFlag && isalnum(c))
            lexeme += c;
        else if (idFlag)
        {
            br->putback(c);
            if(tknTypMap.count(lexeme) == 1)
                return Token(tknTypMap[lexeme], "");
            return Token(T_ID, lexeme);
        }
        if (stringFlag && (c == '\"'))
        {
            lexeme += c;
            return Token(T_SCONST, lexeme);
        }
        else if (stringFlag)
        {
            lexeme += c;
            continue;
        }
        if(br->eof())
            return Token(T_DONE, "");
        if(c == '.')
        {
            lexeme += c;
            return Token(T_ERROR, lexeme);
        }
        if(!isalnum(c))
        {
            lexeme += c;
            return Token(T_DONE, "");
        }
    }
    return Token(T_DONE, "");
}
extern ostream& operator<<(ostream& out, const Token& tok){
    map<TokenType, string> tknTypMap = {
        { T_INT, "T_INT"},
        { T_STRING, "T_STRING"},
        { T_SET, "T_SET"},
        { T_PRINT, "T_PRINT"},
        { T_PRINTLN, "T_PRINTLN"},
        { T_PLUS, "T_PLUS"},
        { T_MINUS, "T_MINUS"},
        { T_STAR, "T_STAR"},
        { T_SLASH, "T_SLASH"},
        { T_LPAREN, "T_LPAREN"},
        { T_RPAREN, "T_RPAREN"},
        { T_SC, "T_SC"},
        { T_ERROR, "T_ERROR"},
        { T_ID, "T_ID"},
        { T_SCONST, "T_SCONST"},
        { T_ICONST, "T_ICONST"}
    };
    if(tok.GetTokenType() == T_ID || tok.GetTokenType() == T_SCONST || tok.GetTokenType() == T_ICONST || tok.GetTokenType() == T_ERROR)
    {
        out << tknTypMap[tok.GetTokenType()] << "(" << tok.GetLexeme() << ")";
        return out;
    }
    out << tknTypMap[tok.GetTokenType()];
    return out;
}
