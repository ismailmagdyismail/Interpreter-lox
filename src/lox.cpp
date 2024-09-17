#include "lox.hpp"
#include "lexer/Lexer.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include <algorithm>
#include <vector>

Lox::Lox(Lexer&& lexer,SourceReport::SourceReporter&& sourceReporter)
:lexer(lexer),sourceReporter(std::move(sourceReporter)){}


std::vector<Tokens::Token> Lox::runLexerPhase()
{
    return lexer.scan(this->sourceReporter);
}

void Lox::runPipeline()
{
    std::vector<Tokens::Token> tokens = lexer.scan(this->sourceReporter);
}
