#pragma once

#include <array>
#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

class Lexer {
   public:
    enum class State : uint32_t {
        Function,
        Header,
        Identifier,
        Comment,
    };

    enum class TokenType {
        Number,
        Identifier,

        LeftParenthesis,
        RightParenthesis,
        LeftBrace,
        RightBrace,
        LeftBracket,
        RightBracket,

        Less,
        Greater,
        Comma,
        Semicolon,
        Exclamation,
        Caret,
        Pipe,
        Hash,

        Plus,
        Minus,
        Asterisk,
        ForwardSlash,
        Equals,

        If,
        Else,
        While,
        For,
        Print,
        KeywordString,
        KeywordInt,
        KeywordBool,
        KeywordChar,
        KeywordArray,

        StringLiteral,
        CharLiteral,

        EndOfFile
    };

    struct TokenIdentity {
        std::string lexeme;
        TokenType type;
    };

    struct TokenSpan {
        size_t line;
        size_t col;
    };

    struct Token {
        TokenIdentity identity;
        TokenSpan span;
    };

    static constexpr std::array<TokenIdentity, 29> token_list{
        {{"(", TokenType::LeftParenthesis},
         {")", TokenType::RightParenthesis},
         {"{", TokenType::LeftBrace},
         {"}", TokenType::RightBrace},
         {"[", TokenType::LeftBracket},
         {"]", TokenType::RightBracket},
         {"<", TokenType::Less},
         {">", TokenType::Greater},
         {",", TokenType::Comma},
         {";", TokenType::Semicolon},
         {"!", TokenType::Exclamation},
         {"^", TokenType::Caret},
         {"|", TokenType::Pipe},
         {"#", TokenType::Hash},
         {"+", TokenType::Plus},
         {"-", TokenType::Minus},
         {"*", TokenType::Asterisk},
         {"/", TokenType::ForwardSlash},
         {"=", TokenType::Equals},
         {"if", TokenType::If},
         {"else", TokenType::Else},
         {"while", TokenType::While},
         {"for", TokenType::For},
         {"print", TokenType::Print},
         {"string", TokenType::KeywordString},
         {"int", TokenType::KeywordInt},
         {"bool", TokenType::KeywordBool},
         {"char", TokenType::KeywordChar},
         {"array", TokenType::KeywordArray}}};

    std::vector<Token> tokenize();
    Lexer(const fs::path file_path);
    Lexer() = delete;
    ~Lexer() = default;

   private:
    std::string m_source;
    fs::path m_file_path;
    TokenIdentity flush_lexeme(std::string_view lexeme);
    std::string peek();
};
