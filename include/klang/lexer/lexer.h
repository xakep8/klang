#pragma once

#include <string>
#include <vector>

class Lexer
{
private:
    enum TokenType
    {
        Number,
        Identifier,
        OpenParen,
        ClostParen,
        BinaryOperator,
        Let,
        Equals
    };
    struct Token
    {
        std::string value;
        TokenType token;
    };

public:
    std::vector<Token> tokenize(std::string &source_code);
};