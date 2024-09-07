#include "lox.hpp"
#include "lexer/Lexer.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include <vector>

Lox::Lox(const Lexer& lexer,const SourceReport::SourceReporter& sourceReporter)
:lexer(lexer),sourceReporter(sourceReporter){}


std::vector<Tokens::Token> Lox::runLexerPhase()
{
    return lexer.scan();
}

void Lox::runPipeline()
{
    std::vector<Tokens::Token> tokens = lexer.scan();
}
