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
    Parser() = default;

    void setTokens(const std::vector<Tokens::Token>& tokens);
    std::vector<std::unique_ptr<Statement::IStatement>> parse(SourceReport::SourceReporter& reporter);
private:
    bool atEnd() const;
    Tokens::Token current() const;
    Tokens::Token peek() const;
    void advance();
    void synchronize();

    //! statements parsers
    std::unique_ptr<Expression::IExpression> expression(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> assignment(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> ternary(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> equality(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> comparison(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> term(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> factor(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> unary(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Expression::IExpression> primary(SourceReport::SourceReporter& reporter);

    //! expressions parsers
    std::unique_ptr<Statement::IStatement> declaration(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> varDeclration(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> statement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> printStatement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> blockStatement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> expressionStatement(SourceReport::SourceReporter& reporter);
    std::unique_ptr<Statement::IStatement> ifStatement(SourceReport::SourceReporter& reporter);

    void checkToken(const Tokens::TokenType& excpectedToknenType, const std::string& errorMessage,SourceReport::SourceReporter& reporter)const;
    unsigned int currentIndex;
    std::vector<Tokens::Token> tokens;
};
