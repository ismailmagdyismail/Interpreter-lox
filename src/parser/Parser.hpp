#pragma once

#include <iostream>
#include <memory>
#include <optional>

#include "expressions/IExpression.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "statements/IStatement.hpp"
#include "tokens/Token.hpp"

class Parser
{
public:
    Parser();

    void setTokens(const std::vector<Tokens::Token>& tokens);
    std::vector<std::unique_ptr<Statement::IStatement>> parse(SourceReport::SourceReporter& reporter);
private:
    bool atEnd() const;
    Tokens::Token current() const;
    Tokens::Token peek() const;
    void advance();
    void synchronize();

    std::unique_ptr<Expression::IExpression> expression(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> ternary(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> equality(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> comparison(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> term(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> factor(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> unary(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> primary(SourceReport::SourceReporter& reporter);

    std::unique_ptr<Statement::IStatement> statement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> printStatement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> expressionStatement(SourceReport::SourceReporter& reporter);

    unsigned int currentIndex;
    std::vector<Tokens::Token> tokens;
};
