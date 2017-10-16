#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <regex>
#include "lexer.h"

using namespace std;

getToken(*istream br)
{
    regex idPattern("[A-Za-Z][A-Za-z0-9]*");
    regex iConstPattern("[0-9]*");
    regex sConstPattern("[\"].*[\"]");
    string lexeme = "";
    while(!isspace(br.peek()))
    {
        lexeme += br.get();
    }
    switch(lexeme)
    {
        case "int":
            return TokenType::T_INT;
            break;
        case "string":
            return TokenType::T_STRING;
            break;
        case "set":
            return TokenType::T_SET;
            break;
        case "print":
            return TokenType::T_PRINT;
            break;
        case "println":
            return TokenType::T_PRINTLN;
            break;
        case "+":
            return TokenType::T_PLUS;
            break;
        case "-":
            return TokenType::T_MINUS;
            break;
        case "*":
            return TokenType::T_STAR;
            break;
        case "/":
            return TokenType::T_SLASH;
            break;
        case "(":
            return TokenType::T_LPAREN;
            break;
        case ")":
            return TokenType::T_RPAREN;
            break;
        case ";":
            return TokenType::T_SC;
            break;
        case null:
            return TokenType::T_DONE;
            break;
        default:
            if(regex_match(lexeme, idPattern))
            {
                return TokenType::T_ID;
                break;
            }
            else if(regex_match(lexeme, sConstPattern))
            {
                return TokenType::T_SCONST;
                break;
            }
            else if(regex_match(lexeme, iConstPattern))
            {
                return TokenType::T_ICONST;
                break;
            }
            else
            {
                return TokenType::T_ERROR;
                break;
            }
    }
}