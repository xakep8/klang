#include <klang/lexer/lexer.h>

#include <iostream>

static std::vector<std::string> split_string(std::string& source_code) {
    std::vector<std::string> source_strings;
    char last_char = ' ';
    while (last_char != ' ') {
    }
    return source_strings;
}

std::vector<Lexer::Token> Lexer::tokenize(std::string& source_code) {
    std::vector<Token> tokens;
    std::cout << "Hey from the lexer module!\n";
    // std::vector<std::string> src = split_string(source_code);
    return tokens;
}