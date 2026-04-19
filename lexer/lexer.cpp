#include <klang/lexer/lexer.h>

#include <iostream>

static std::vector<std::string> split_string(std::string& source_code) {
    std::vector<std::string> source_strings;
    std::string word = "";
    for (char i : source_code) {
        if (i != ' ') {
            word += i;
        } else {
            source_strings.push_back(word);
            word = "";
        }
    }
    if (word != "") {
        source_strings.push_back(word);
    }
    return source_strings;
}

std::vector<Lexer::Token> Lexer::tokenize(std::string& source_code) {
    std::vector<Token> tokens;
    std::vector<std::string> src = split_string(source_code);
    for (auto i : src) {
        std::cout << i << "\n";
    }
    return tokens;
}