#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <regex>
#include "lexer.h"

using namespace std;

class Tokenizer
{
    public:
        extern Token getToken(*istream br);
        Tokenizer();
};
Tokenizer::Tokenizer()
{
}
Tokenizer::getToken(*istream br)
{
    regex idPattern("[a-Z]");
    regex iConstPattern();
    regex sConstPattern();
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
        default:

    }
}