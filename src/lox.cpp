#include "lox.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/GroupedExpression.hpp"
#include "ast/IExpression.hpp"
#include "ast/IVisitor.hpp"
#include "ast/LiteralExpression.hpp"
#include "ast/UnaryExpression.hpp"
#include "astFormatter/AstPrinter.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include "utils/GenericType.hpp"


#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>

Lox::Lox(Lexer&& lexer,Parser&& parser,SourceReport::SourceReporter&& sourceReporter)
:lexer(lexer),sourceReporter(std::move(sourceReporter)){}


std::vector<Tokens::Token> Lox::runLexerPhase()
{
    return lexer.scan(this->sourceReporter);
}

void Lox::runPipeline()
{
    std::vector<Tokens::Token> tokens = lexer.scan(this->sourceReporter);
    parser.setTokens(tokens);
    std::unique_ptr<Expression::IExpression> expression = parser.parse(this->sourceReporter);
    AstPrinter printer ;
    std::cout<<GenericType::toString(expression->accept(printer))<<'\n';
}
