#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "exceptions/ParserError.hpp"
#include "expressions/AssignmentExpression.hpp"
#include "expressions/GroupedExpression.hpp"
#include "expressions/LiteralExpression.hpp"
#include "expressions/TernaryExpression.hpp"
#include "expressions/VariableExpression.hpp"
#include "parser/Parser.hpp"
#include "Parser.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineError.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "statements/ExpressionStatement.hpp"
#include "statements/IStatement.hpp"
#include "statements/PrintStatement.hpp"
#include "statements/VarStatement.hpp"
#include "tokens/Token.hpp"

void Parser::setTokens(const std::vector<Tokens::Token> &tokens)
{
    this->currentIndex = 0;
    this->tokens = tokens;
}

bool Parser::atEnd() const
{
    return current().tokenType == Tokens::TokenType::END_OF_FILE;
}

Tokens::Token Parser::current() const
{
    return this->tokens[this->currentIndex];
}

Tokens::Token Parser::peek() const
{
    if(atEnd())
    {
        return current();
    }
    return this->tokens[currentIndex + 1];
}

void Parser::advance()
{
    if(!atEnd())
    {
        this->currentIndex++;
    }
}

std::vector<std::unique_ptr<Statement::IStatement>> Parser::parse(SourceReport::SourceReporter& reporter)
{
    std::vector<std::unique_ptr<Statement::IStatement>> statements;
    while (!atEnd())
    {
        statements.push_back(declration(reporter));
    }
    return statements;
}

std::unique_ptr<Statement::IStatement> Parser::declration(SourceReport::SourceReporter& reporter)
{
    try
    {
        if(current().tokenType == Tokens::TokenType::VAR)
        {
            return varDeclration(reporter);
        }
        return statement(reporter);
    }
    catch(const ParserError& error)
    {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Statement::IStatement> Parser::varDeclration(SourceReport::SourceReporter& reporter)
{
    advance(); // skip var keyword
    if(current().tokenType != Tokens::TokenType::IDENTFIER)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Excpected IDENTFIER");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        throw ParserError(current(),"Excpected IDENTFIER");
    }
    Tokens::Token identifier = current();
    advance(); // skipt Identifier
    if(current().tokenType != Tokens::TokenType::ASSIGN)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Excpected =");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        throw ParserError(current(),"Excpected =");
    }
    advance(); // skip =
    auto value = expression(reporter);
    if(current().tokenType != Tokens::TokenType::SEMI_COLON)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Excpected ;");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        throw ParserError(current(),"Excpected ;");
    }
    advance(); // skip ;
    return std::make_unique<Statement::VarStatement>(identifier,std::move(value));
}

std::unique_ptr<Statement::IStatement> Parser::statement(SourceReport::SourceReporter& reporter)
{
    if(current().tokenType == Tokens::TokenType::PRINT)
    {
        return printStatement(reporter);
    }
    return expressionStatement(reporter);
}

std::unique_ptr<Statement::IStatement> Parser::printStatement(SourceReport::SourceReporter& reporter)
{
    advance(); // skip print token
    std::unique_ptr<Expression::IExpression> parsedExpression = expression(reporter);
    if(current().tokenType != Tokens::TokenType::SEMI_COLON)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Excepected ;");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        throw ParserError(current(),"Excepected ;");
    }
    advance(); // skip ;
    return std::make_unique<Statement::PrintStatement>(std::move(parsedExpression));
}

std::unique_ptr<Statement::IStatement> Parser::expressionStatement(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> parsedExpression = expression(reporter);
    if(current().tokenType != Tokens::TokenType::SEMI_COLON)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Excepected ;");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        throw ParserError(current(),"Excepected ;");
    }
    advance(); // skip ;
    return std::make_unique<Statement::ExpressionStatement>(std::move(parsedExpression));
}

std::unique_ptr<Expression::IExpression> Parser::expression(SourceReport::SourceReporter& reporter)
{
    return assignment(reporter);
}

std::unique_ptr<Expression::IExpression> Parser::assignment(SourceReport::SourceReporter& reporter)
{
   auto lValue = ternary(reporter);
   if(current().tokenType == Tokens::TokenType::ASSIGN)
   {
       advance(); // skip =
       std::unique_ptr<Expression::IExpression> value = assignment(reporter);
       auto variableExpression =  dynamic_cast<Expression::VariableExpression*>(lValue.get()) ;
       if(variableExpression != nullptr)
       {
           return std::make_unique<Expression::AssignmentExpression>(Expression::AssignmentExpression(variableExpression->identifer,std::move(value)));
       }
   }
   return lValue;
}

std::unique_ptr<Expression::IExpression> Parser::ternary(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> expression = equality(reporter);
    while (current().tokenType == Tokens::TokenType::QUESTION_MARK)
    {
        advance(); // skip ?
        std::unique_ptr<Expression::IExpression> truthBranch = equality(reporter);
        if(current().tokenType != Tokens::TokenType::COLON)
        {
            SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Expect :");
            reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
            throw ParserError(current(),"No : was found for ternary operatry");
        }
        advance(); // skip :
        std::unique_ptr<Expression::IExpression> falseBranch = equality(reporter);
        expression = std::make_unique<Expression::TernaryExpression>(
            Expression::TernaryExpression(std::move(expression),std::move(truthBranch),std::move(falseBranch))
        );
    }
    return expression;
}

std::unique_ptr<Expression::IExpression> Parser::equality(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> expression = comparison(reporter);
    while (
        current().tokenType == Tokens::TokenType::EQUAL ||
        current().tokenType == Tokens::TokenType::BANG_EQUAL
    )
    {
        Tokens::Token token = current();
        advance(); // skip equality operator
        std::unique_ptr<Expression::IExpression> rhs = comparison(reporter);
        expression = std::make_unique<Expression::BinaryExpression>(
            Expression::BinaryExpression(std::move(expression),token,std::move(rhs))
        );
    }
    return expression;
}

std::unique_ptr<Expression::IExpression> Parser::comparison(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> expression = term(reporter);
    while(
        current().tokenType == Tokens::TokenType::GREATER ||
        current().tokenType == Tokens::TokenType::SMALLER ||
        current().tokenType == Tokens::TokenType::SMALLER_OR_EQUAL ||
        current().tokenType == Tokens::TokenType::GREATER_OR_EQUAL
    )
    {
        Tokens::Token token = current();
        advance(); // skip comparison operator
        std::unique_ptr<Expression::IExpression> rhs = term(reporter);
        expression = std::make_unique<Expression::BinaryExpression>(
            Expression::BinaryExpression(std::move(expression),token,std::move(rhs))
        );
    }
    return expression;
}


std::unique_ptr<Expression::IExpression> Parser::term(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> expression = factor(reporter);
    while(current().tokenType == Tokens::TokenType::PLUS || current().tokenType == Tokens::TokenType::MINUS)
    {
        Tokens::Token token = current();
        advance(); // skip term operatror (+ OR -)
        std::unique_ptr<Expression::IExpression> rhs = factor(reporter);
        expression = std::make_unique<Expression::BinaryExpression>(
            Expression::BinaryExpression(std::move(expression),token,std::move(rhs))
        );
    }
    return expression;
}

std::unique_ptr<Expression::IExpression> Parser::factor(SourceReport::SourceReporter& reporter)
{
    std::unique_ptr<Expression::IExpression> expression = unary(reporter);
    while(current().tokenType == Tokens::TokenType::STAR || current().tokenType == Tokens::TokenType::SLASH)
    {
        Tokens::Token token = current();
        advance(); // skip Factor operatror (* OR /)
        std::unique_ptr<Expression::IExpression> rhs = unary(reporter);
        expression = std::make_unique<Expression::BinaryExpression>(
            Expression::BinaryExpression(std::move(expression),token,std::move(rhs))
        );
    }
    return expression;
}

std::unique_ptr<Expression::IExpression> Parser::unary(SourceReport::SourceReporter& reporter)
{
    if(current().tokenType == Tokens::TokenType::MINUS || current().tokenType == Tokens::TokenType::BANG)
    {
        Tokens::Token unaryOperator = current();
        advance(); // skip initial unaryOperator
        std::unique_ptr<Expression::IExpression> rhs  = unary(reporter);
        return std::make_unique<Expression::UnaryExpression>(
            Expression::UnaryExpression(unaryOperator,std::move(rhs))
        );
    }
    return primary(reporter);
}


std::unique_ptr<Expression::IExpression> Parser::primary(SourceReport::SourceReporter& reporter)
{
    Tokens::TokenType tokenType = current().tokenType;

    if(tokenType == Tokens::TokenType::NIL)
    {
        advance(); // skip NIL litral
        return std::make_unique<Expression::LiteralExpression>(
            Expression::LiteralExpression(nullptr)
        );
    }
    if(tokenType == Tokens::TokenType::TRUE)
    {
        advance(); // skip boolean literal
        return std::make_unique<Expression::LiteralExpression>(
            Expression::LiteralExpression(true)
        );
    }
    if(tokenType == Tokens::TokenType::FALSE)
    {
        advance(); // skip boolean literal
        return std::make_unique<Expression::LiteralExpression>(
            Expression::LiteralExpression(false)
        );
    }
    if(tokenType == Tokens::TokenType::NUMBER)
    {
        Tokens::Token numberLiteralToken = current();
        advance(); // skip number literal
        return std::make_unique<Expression::LiteralExpression>(
            Expression::LiteralExpression(std::stod(numberLiteralToken.lexeme))
        );
    }
    if(tokenType == Tokens::TokenType::IDENTFIER)
    {
        Tokens::Token idenetifier = current();
        advance();
        return std::make_unique<Expression::VariableExpression>(
            Expression::VariableExpression(idenetifier)
        );
    }
    if(tokenType == Tokens::TokenType::STRING)
    {
        Tokens::Token stringLiteralToken = current();
        advance(); // skip string literal
        return std::make_unique<Expression::LiteralExpression>(
            Expression::LiteralExpression(stringLiteralToken.lexeme)
        );
    }
    if(tokenType == Tokens::TokenType::LEFT_PARNTHESES)
    {
        advance(); // skip starting (
        std::unique_ptr<Expression::IExpression> groupedExpression = expression(reporter);
        if(current().tokenType != Tokens::TokenType::RIGHT_PARNTHESES)
        {
            SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"No closing ) was found");
            reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
            throw ParserError(current(),"No closing ) was found");
        }
        advance(); // skip ending )
        return std::make_unique<Expression::GroupedExpression>(
            Expression::GroupedExpression(std::move(groupedExpression))
        );
    }
    SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Expect expression");
    reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
    throw ParserError(current(),"Expect expression");
}

void Parser::synchronize()
{
    advance();
    while(
        !atEnd() &&
        (current().tokenType != Tokens::TokenType::SEMI_COLON ||
        current().tokenType != Tokens::TokenType::CLASS ||
        current().tokenType != Tokens::TokenType::FUNCTION ||
        current().tokenType != Tokens::TokenType::VAR ||
        current().tokenType != Tokens::TokenType::FOR ||
        current().tokenType != Tokens::TokenType::IF ||
        current().tokenType != Tokens::TokenType::WHILE ||
        current().tokenType != Tokens::TokenType::PRINT ||
        current().tokenType != Tokens::TokenType::RETURN)
    )
    {
        advance();
    }
}
