#include "lox.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/GroupedExpression.hpp"
#include "ast/IExpression.hpp"
#include "ast/IVisitor.hpp"
#include "ast/LiteralExpression.hpp"
#include "ast/UnaryExpression.hpp"
#include "astFormatter/AstPrinter.hpp"
#include "interpreter/Interpreter.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"
#include "object/Object.hpp"


#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>

Lox::Lox(Lexer&& lexer,Parser&& parser,Interpreter&& interpreter,SourceReport::SourceReporter&& sourceReporter)
:lexer(std::move(lexer)),interpreter(std::move(interpreter)),sourceReporter(std::move(sourceReporter)){}


std::vector<Tokens::Token> Lox::runLexerPhase()
{
    return lexer.scan(this->sourceReporter);
}

void Lox::runPipeline()
{
    bool (*errorChecker)(SourceReport::SourceReporter&) = [](SourceReport::SourceReporter& reporter)-> bool {
        if(reporter.hasError())
        {
            auto messages = reporter.formatReports(SourceReport::ReportMessageLevel::Error);
            for(auto& message : messages)
            {
                std::cout<<message<<'\n';
            }
        }
        return reporter.hasError();
    };
    std::vector<Tokens::Token> tokens = lexer.scan(this->sourceReporter);
    if(errorChecker(this->sourceReporter))
    {
        return;
    }
    parser.setTokens(tokens);
    std::unique_ptr<Expression::IExpression> expression = parser.parse(this->sourceReporter);
    if(errorChecker(this->sourceReporter))
    {
        return;
    }
    AstPrinter printer ;
    std::cout<<Object::toString(expression->accept(printer))<<'\n';

    std::any result = interpreter.interpret(expression,this->sourceReporter);
    if(errorChecker(this->sourceReporter))
    {
        return;
    }
    if(result.has_value())
    {
        std::cout<<Object::toString(result)<<'\n';
    }
}
