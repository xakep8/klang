#include <klang/lexer/lexer.h>

#include <fstream>

Lexer::TokenIdentity Lexer::flush_lexeme(std::string_view lexeme) {
    for (const auto& token : token_list) {
        if (lexeme == token.lexeme) {
            return token;
        }
    }
    return {std::string(lexeme), TokenType::Identifier};
}

Lexer::Lexer(const fs::path file_path) {
    m_file_path = file_path;
    std::ifstream file(file_path);
    std::string source_code = "";
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            source_code += line;
            source_code += '\n';
        }
        file.close();
    }
    m_source = source_code;
}

std::vector<Lexer::Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    size_t line_itr = 1;
    size_t col_itr = 1;
    std::string lexeme = "";
    for (size_t i{0uz}; i < m_source.size(); i++) {
        if (m_source[i] == '\n') {
            if (!lexeme.empty()) {
                tokens.push_back({flush_lexeme(lexeme),
                                  {line_itr, col_itr - lexeme.size()}});
            }
            lexeme = "";
            col_itr = 1;
            line_itr++;
        } else if (!isspace(static_cast<unsigned char>(m_source[i]))) {
            if (isalnum(static_cast<unsigned char>(m_source[i]))) {
                lexeme += m_source[i];
                col_itr++;
            } else {
                if (!lexeme.empty()) {
                    tokens.push_back({flush_lexeme(lexeme),
                                      {line_itr, col_itr - lexeme.size()}});
                }
                std::string_view symbol = m_source.substr(i, 1);
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
