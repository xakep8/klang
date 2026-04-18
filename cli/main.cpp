#include <klang/lexer/lexer.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

namespace fs = std::filesystem;

struct CommandContext {
    int argc;
    char** argv;
};

using CommandHandler = int (*)(const CommandContext&);

int handle_lex(const CommandContext&);
int handle_version(const CommandContext&);
int handle_help(const CommandContext&);
int handle_run(const CommandContext&);
int handle_check(const CommandContext&);
int handle_parse(const CommandContext&);
int handle_dis(const CommandContext&);
int handle_ast(const CommandContext&);
int handle_fmt(const CommandContext&);
int handle_compile(const CommandContext&);
int handle_exec(const CommandContext&);
int handle_repl(const CommandContext&);

struct CommandSpec {
    std::string_view name;
    std::string_view description;
    CommandHandler handler;
};

constexpr std::array<CommandSpec, 12> kCommands{
    {{"help", "Show help", handle_help},
     {"version", "Show version", handle_version},
     {"lex", "Tokenize a source file", handle_lex},
     {"run", "Run a source file", handle_run},
     {"check", "Validate a source file", handle_check},
     {"parse", "Parse a source file", handle_parse},
     {"dis", "Disassemble bytecode", handle_dis},
     {"ast", "Print AST for the source file", handle_ast},
     {"fmt", "Format a source file", handle_fmt},
     {"compile", "Compile source to bytecode", handle_compile},
     {"exec", "Execute bytecode file", handle_exec},
     {"repl", "Start interactive REPL", handle_repl}}};

const CommandSpec* find_command(std::string_view name) {
    for (const auto& cmd : kCommands) {
        if (cmd.name == name) {
            return &cmd;
        }
    }
    return nullptr;
}

int handle_lex(const CommandContext& ctx) {
    fs::path p(ctx.argv[2]);
    if (!fs::exists(p)) {
        std::cerr << "Invalid File Path\n";
        return handle_help(ctx);
    }

    std::ifstream file(p);
    Lexer lexer;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lexer.tokenize(line);
        }
        file.close();
    }
    return 0;
}
int handle_version(const CommandContext& ctx) {
    std::cout << "klang 0.1.0\n";
    return 0;
}
int handle_help(const CommandContext& ctx) {
    std::cout << "klang <command> [args]\n\nCommands:\n";
    for (const auto& cmd : kCommands) {
        std::cout << "  " << cmd.name << " - " << cmd.description << '\n';
    }
    return 0;
}
int handle_run(const CommandContext& ctx) {
    std::cout << "run\n";
    return 0;
}
int handle_check(const CommandContext& ctx) {
    std::cout << "check\n";
    return 0;
}
int handle_parse(const CommandContext& ctx) {
    std::cout << "parse\n";
    return 0;
}
int handle_dis(const CommandContext& ctx) {
    std::cout << "disassemble\n";
    return 0;
}
int handle_ast(const CommandContext& ctx) {
    std::cout << "ast\n";
    return 0;
}
int handle_fmt(const CommandContext& ctx) {
    std::cout << "fmt\n";
    return 0;
}
int handle_compile(const CommandContext& ctx) {
    std::cout << "compile\n";
    return 0;
}
int handle_exec(const CommandContext& ctx) {
    std::cout << "exec\n";
    return 0;
}
int handle_repl(const CommandContext& ctx) {
    std::cout << "repl\n";
    return 0;
}

int main(int argc, char** argv) {
    CommandContext ctx{argc, argv};

    if (argc < 2) {
        return handle_help(ctx);
    }

    std::string_view command_name = argv[1];
    const CommandSpec* cmd = find_command(command_name);

    if (!cmd) {
        std::cerr << "Unknown command: " << command_name << '\n';
        return handle_help(ctx);
    }

    return cmd->handler(ctx);
}