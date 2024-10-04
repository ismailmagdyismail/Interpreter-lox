#pragma once

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include <vector>

class Lox
{
public:
    Lox(Lexer&& lexer,Parser&& parser,SourceReport::SourceReporter&& reporter);
    void runPipeline();
    std::vector<Tokens::Token> runLexerPhase();

 private:
    Lexer lexer;
    Parser parser;
    SourceReport::SourceReporter sourceReporter;
};
