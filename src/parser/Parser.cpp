#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include "expressions/GroupedExpression.hpp"
#include "expressions/LiteralExpression.hpp"
#include "expressions/TernaryExpression.hpp"
#include "parser/Parser.hpp"
#include "Parser.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineError.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"

Parser::Parser()
{}

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

std::unique_ptr<Expression::IExpression> Parser::parse(SourceReport::SourceReporter& reporter)
{
    try
    {
       return expression(reporter);
    }
    catch(const std::exception& exception)
    {
        return nullptr;
    }
}

std::unique_ptr<Expression::IExpression> Parser::expression(SourceReport::SourceReporter& reporter)
{
    return ternary(reporter);
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
            throw std::runtime_error("No : was found for ternary operatry");
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
            throw std::runtime_error("No closing ) was found");
        }
        advance(); // skip ending )
        return std::make_unique<Expression::GroupedExpression>(
            Expression::GroupedExpression(std::move(groupedExpression))
        );
    }
    SourceReport::LineError lineError(SourceReport::LineDescriptor(current().lineNumber),"Expect expression");
    reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
    throw std::runtime_error("Expect expression");
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
