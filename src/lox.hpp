#pragma once


#include "lexer/Lexer.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include <vector>
class Lox
{
public:
    Lox(const Lexer& lexer,const SourceReport::SourceReporter& reporter);
    void runPipeline();
    std::vector<Tokens::Token> runLexerPhase();

 private:
    Lexer lexer;
    SourceReport::SourceReporter sourceReporter;
};
