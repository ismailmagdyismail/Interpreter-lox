#include "lox.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/GroupedExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"
#include "expressions/LiteralExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "expressionsFormatter/ExpressionPrinter.hpp"
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
    auto statements = parser.parse(this->sourceReporter);
    if(errorChecker(this->sourceReporter))
    {
        std::cout<<"[Error]: error in parsing stage ";
        return;
    }
    interpreter.interpret(statements,this->sourceReporter);
    if(errorChecker(this->sourceReporter))
    {
        std::cout<<"[Error]: error in Interpreter stage ";
        return;
    }
}
