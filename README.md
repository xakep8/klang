# klang

klang is a small C++20 compiler project I am building from the ground up.
It is intentionally modest in scope: the goal is to keep the codebase easy to
read while the pieces of a real language toolchain are put together one by one.

Right now the repository is organized as a few focused modules:

- `lexer/` for turning source text into tokens
- `parser/` for building syntax structure from those tokens
- `ast/` for the abstract syntax tree layer
- `compiler/` for lowering the AST into something executable
- `vm/` for running compiled output
- `debug/` for inspection and disassembly helpers
- `cli/` for the command-line entry point
- `tests/` for smoke tests and build verification

The CLI already exposes the command names I want to grow into:

- `help`
- `version`
- `lex`
- `run`
- `check`
- `parse`
- `dis`
- `ast`
- `fmt`
- `compile`
- `exec`
- `repl`

Only a few of those commands do real work today, and that is by design. The
project is being built in the open, so the README should reflect the actual
state of the code rather than a future version of it.

## Building

This repo uses CMake presets and a small helper script.

Build only the CLI:

```bash
bash ./build.sh cli
```

Build everything and run the test suite:

```bash
bash ./build.sh
```

If you prefer to work directly with the CMake preset, the debug preset is the
one in use.

## Running the CLI

After a build, the CLI binary is available at:

```bash
./build/debug/klang_cli
```

Run the help output:

```bash
./build/debug/klang_cli help
```

Try the lexer command against a source file:

```bash
./build/debug/klang_cli lex path/to/file.kl
```

At the moment, `lex` checks that the file exists and feeds its contents into
the lexer. Token printing is still a work in progress, so do not expect a full
token stream yet.

## Current Shape Of The Code

The current layout is simple on purpose. `klang_core` is the library target
that ties the modules together, and `klang_cli` is the executable that gives
the project a usable front door.

The lexer interface currently exposes tokenization only, and the surrounding
modules are mostly scaffolding for the next stages of the compiler pipeline.

## Notes

This repository is in active development. The safest way to think about it is:

- the build works
- the CLI scaffolding works
- the language pipeline is being filled in module by module

If you are reading this to understand how to contribute, the best starting
point is whichever module you want to make real next.