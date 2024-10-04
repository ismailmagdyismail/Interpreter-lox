#pragma once

#include <iostream>
#include <memory>
#include <optional>

#include "ast/IExpression.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"

class Parser
{
public:
    Parser();

    void setTokens(const std::vector<Tokens::Token>& tokens);
    std::unique_ptr<Expression::IExpression> parse(SourceReport::SourceReporter& reporter);
private:
    bool atEnd() const;
    Tokens::Token current() const;
    Tokens::Token peek() const;
    void advance();
    void synchronize();

    std::unique_ptr<Expression::IExpression> expression(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> equality(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> comparison(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> term(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> factor(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> unary(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> primary(SourceReport::SourceReporter& reporter);

    unsigned int currentIndex;
    std::vector<Tokens::Token> tokens;
};
