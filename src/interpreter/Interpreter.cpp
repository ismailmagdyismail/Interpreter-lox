#include <any>
#include <iostream>
#include <memory>
#include <sys/_types/_caddr_t.h>
#include <vector>

//! interpreter
#include "interpreter/Interpreter.hpp"

//! enviroment
#include "enviroment/Enviroment.hpp"

//! expressions
#include "expressions/AssignmentExpression.hpp"
#include "expressions/TernaryExpression.hpp"
#include "expressions/VariableExpression.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/LiteralExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "expressions/GroupedExpression.hpp"

//! error reporter
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineError.hpp"

//! statements
#include "statements/BlockStatement.hpp"
#include "statements/ExpressionStatement.hpp"
#include "statements/IStatement.hpp"
#include "statements/PrintStatement.hpp"
#include "statements/VarStatement.hpp"
#include "statements/IfStatement.hpp"
#include "statements/WhileStatement.hpp"
#include "statements/ForStatement.hpp"

//! types
#include "tokens/Token.hpp"
#include "object/Object.hpp"

//! exceptions
#include "exceptions/LoxError.hpp"
#include "exceptions/TypeError.hpp"

//! utilites
#include "stringBuilder/StringBuilder.hpp"

static bool isTruthy(std::any object)
{
    if(!object.has_value())
    {
        return false;
    }
    if(object.type() == typeid(bool))
    {
        return std::any_cast<bool>(object);
    }
    return true;
}

void Interpreter::interpret(const std::vector<std::unique_ptr<Statement::IStatement>>& statements,SourceReport::SourceReporter& reporter)
{
    for(auto& statement : statements)
    {
        try
        {
            statement->accept(*this);
        }
        catch(LoxError& error)
        {
            SourceReport::LineError lineError(SourceReport::LineDescriptor(error.token.lineNumber),error.errorMessage());
            reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        }
    }
}

std::any Interpreter::visitExpressionStatement(const Statement::ExpressionStatement& expressionStatement)
{
    expressionStatement.expression->accept(*this);
    return nullptr;
}


std::any Interpreter::visitPrintStatement(const Statement::PrintStatement& printStatement)
{
    std::any value = printStatement.expression->accept(*this);
    std::cout<<Object::toString(value)<<'\n';
    return nullptr;
}

std::any Interpreter::visitVarStatement(const Statement::VarStatement& varStatement)
{
    std::any value = varStatement.value->accept(*this);
    environment.bind(varStatement.identifier, value);
    return nullptr;
}

std::any Interpreter::visitBlockStatement(const Statement::BlockStatement& blockStatement)
{
    // Save the current environment to restore it later
    try
    {
        // Create a new environment with the previous environment as the parent
        environment.pushScope();
        for (auto& statement : blockStatement.statements)
        {
            statement->accept(*this);
        }
        // Restore the previous environment
        environment.popScope();
    }
    catch (const LoxError& error)
    {
        // Restore the previous environment in case of an error
        environment.popScope();
        throw;
    }

    // Return a null value indicating the end of the block
    return nullptr;
}

std::any Interpreter::visitIfStatement(const Statement::IfStatement& ifStatement)
{
    std::any conditionResult = ifStatement.condition->accept(*this);
    if(isTruthy(conditionResult))
    {
        ifStatement.trueBranchStatements->accept(*this);
    }
    else if(ifStatement.falseBranchStatements.has_value())
    {
        ifStatement.falseBranchStatements.value()->accept(*this);
    }
    return nullptr;
}

std::any Interpreter::visitWhileStatement(const Statement::WhileStatement& whileStatement)
{
    std::any conditionResult = whileStatement.condition->accept(*this);
    while(isTruthy(conditionResult))
    {
        whileStatement.loopBody->accept(*this);
        conditionResult = whileStatement.condition->accept(*this);
    }
    return nullptr;
}

std::any Interpreter::visitForStatement(const Statement::ForStatement& forStatement)
{
    environment.pushScope();
    if(forStatement.initialization != nullptr)
    {
        forStatement.initialization->accept(*this);
    }
    std::any conditionResult = true;
    if(forStatement.condition != nullptr)
    {
        conditionResult = forStatement.condition->accept(*this);
    }
    while(isTruthy(conditionResult))
    {
        forStatement.loopBody->accept(*this);
        if(forStatement.increment != nullptr)
        {
            forStatement.increment->accept(*this);
        }
        if(forStatement.condition != nullptr)
        {
            conditionResult = forStatement.condition->accept(*this);
        }
    }
    environment.popScope();

    return nullptr;
}


std::any Interpreter::visitBinaryExpression(const Expression::BinaryExpression &binaryExpression)
{
    std::any leftExpressionValue = binaryExpression.leftOperand->accept(*this);
    std::any rightExpressionValue = binaryExpression.rightOperand->accept(*this);

    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::PLUS)
    {
        if(Object::typeChecker<std::string>(leftExpressionValue,rightExpressionValue))
        {
            return std::any_cast<std::string>(leftExpressionValue) + std::any_cast<std::string>(rightExpressionValue);
        }
        if(Object::typeChecker<std::string>(leftExpressionValue) && Object::typeChecker<double>(rightExpressionValue))
        {
            return std::any_cast<std::string>(leftExpressionValue) + Object::toString(rightExpressionValue);
        }
        if(Object::typeChecker<double>(leftExpressionValue) && Object::typeChecker<std::string>(rightExpressionValue))
        {
            return Object::toString(leftExpressionValue) + Object::toString(rightExpressionValue);
        }
        if(Object::typeChecker<double>(leftExpressionValue, rightExpressionValue))
        {
            return std::any_cast<double>(leftExpressionValue) + std::any_cast<double>(rightExpressionValue);
        }
        throw TypeError(binaryExpression.binaryOperator,"Operators must be Numbers or strings");
    }
    std::function<std::any(std::any(*callback)(double left,double right))>numbersTypeMatching =
    [&leftExpressionValue,&rightExpressionValue,&binaryExpression](std::any(*callback)(double left,double right))->std::any
    {
        if(!Object::typeChecker<double>(leftExpressionValue, rightExpressionValue))
        {
            throw TypeError(binaryExpression.binaryOperator,"Operators Must be Numbers");
        }
        return callback(std::any_cast<double>(leftExpressionValue),std::any_cast<double>(rightExpressionValue));
    };
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::MINUS)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left - right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::SLASH)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left / right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::STAR)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left * right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::GREATER)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left > right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::SMALLER)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left < right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::GREATER_OR_EQUAL)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left >= right;
        });
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::SMALLER_OR_EQUAL)
    {
        return numbersTypeMatching([](double left,double right)->std::any{
            return left <= right;
        });
    }

    std::function<bool()> equalityCheck = [&leftExpressionValue,&rightExpressionValue]()->bool
    {
        if(!leftExpressionValue.has_value() && !rightExpressionValue.has_value())
        {
            return true;
        }
        if(!leftExpressionValue.has_value() || !rightExpressionValue.has_value())
        {
            return false;
        }
        if(leftExpressionValue.type() != rightExpressionValue.type())
        {
            return false;
        }
        return Object::toString(leftExpressionValue) == Object::toString(rightExpressionValue);
    };
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::EQUAL)
    {
        return equalityCheck();
    }
    if(binaryExpression.binaryOperator.tokenType == Tokens::TokenType::BANG_EQUAL)
    {
        return !equalityCheck();
    }
    throw TypeError(binaryExpression.binaryOperator,"Operators Not recognized");
}



std::any Interpreter::visitUnaryExpression(const Expression::UnaryExpression &unaryExpression)
{
    std::any expressionResult = unaryExpression.operand->accept(*this);
    if(unaryExpression.unaryOperator.tokenType == Tokens::TokenType::BANG)
    {
       return !isTruthy(expressionResult);
    }
    if(unaryExpression.unaryOperator.tokenType == Tokens::TokenType::MINUS && Object::typeChecker<double>(expressionResult))
    {
        return -std::any_cast<double>(expressionResult);
    }
    if(unaryExpression.unaryOperator.tokenType == Tokens::TokenType::MINUS)
    {
        throw TypeError(unaryExpression.unaryOperator,"Cannot apply - to a non Numeric Operand");
    }
    throw TypeError(unaryExpression.unaryOperator,"Operators Not recognized");
}

std::any Interpreter::visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression)
{
    std::any condition = ternaryExpression.condition->accept(*this);
    if(isTruthy(condition))
    {
        return ternaryExpression.trueExpression->accept(*this);
    }
    return ternaryExpression.falseExpression->accept(*this);
}

std::any Interpreter::visitGroupedExpression(const Expression::GroupedExpression &groupedExpression)
{
    return groupedExpression.groupedExpression->accept(*this);
}

std::any Interpreter::visitLiteralExpression(const Expression::LiteralExpression &literalExpression)
{
    return literalExpression.value;
}

std::any Interpreter::visitVariableExpression(const Expression::VariableExpression &variableExpression)
{
    return environment.read(variableExpression.identifer);
}


std::any Interpreter::visitAssignmentExpression(const Expression::AssignmentExpression &assignmentExpression)
{
    // leaky abstraction of "=" token structure
    std::any value = assignmentExpression.value->accept(*this);
    environment.assign(assignmentExpression.idenetifier,value);
    return value;
}
