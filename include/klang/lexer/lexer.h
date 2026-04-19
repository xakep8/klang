#pragma once

#include <string>
#include <vector>

class Lexer {
   public:
    enum TokenType {
        Number,
        Identifier,
        OpenParen,
        ClostParen,
        BinaryOperator,
        Equals
    };
    struct Token {
        std::string value;
        TokenType token;
    };

    std::vector<Token> tokenize(std::string& source_code);
};