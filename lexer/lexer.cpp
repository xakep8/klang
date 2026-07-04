#include <klang/lexer/lexer.h>

#include <iostream>

Lexer::TokenIdentity Lexer::flush_lexeme(std::string_view lexeme) {
    for (const auto& token : token_list) {
        if (lexeme == token.lexeme) {
            return token;
        }
    }
    return {std::string(lexeme), TokenType::Identifier};
}

std::vector<Lexer::Token> Lexer::tokenize(std::string_view source_code) {
    std::vector<Token> tokens;
    size_t line_itr = 1;
    size_t col_itr = 1;
    std::string lexeme = "";
    for (size_t i{0uz}; i < source_code.size(); i++) {
        if (source_code[i] == '\n') {
            if (!lexeme.empty()) {
                tokens.push_back({flush_lexeme(lexeme),
                                  {line_itr, col_itr - lexeme.size()}});
            }
            lexeme = "";
            col_itr = 1;
            line_itr++;
        } else if (!isspace(static_cast<unsigned char>(source_code[i]))) {
            if (isalnum(static_cast<unsigned char>(source_code[i]))) {
                lexeme += source_code[i];
                col_itr++;
            } else {
                if (!lexeme.empty()) {
                    tokens.push_back({flush_lexeme(lexeme),
                                      {line_itr, col_itr - lexeme.size()}});
                }
                std::string_view symbol = source_code.substr(i, 1);
                tokens.push_back({flush_lexeme(symbol), {line_itr, col_itr}});
                lexeme = "";
                col_itr++;
            }
        } else {
            if (!lexeme.empty()) {
                tokens.push_back({flush_lexeme(lexeme),
                                  {line_itr, col_itr - lexeme.size()}});
            }
            lexeme = "";
            col_itr++;
        }
    }
    if (!lexeme.empty()) {
        tokens.push_back(
            {flush_lexeme(lexeme), {line_itr, col_itr - lexeme.size()}});
    }
    return tokens;
}