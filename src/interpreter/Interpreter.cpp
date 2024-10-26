#include <any>
#include <iostream>

#include "expressions/TernaryExpression.hpp"
#include "exceptions/LoxError.hpp"
#include "exceptions/TypeError.hpp"
#include "interpreter/Interpreter.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/LiteralExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "expressions/GroupedExpression.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineError.hpp"
#include "tokens/Token.hpp"
#include "object/Object.hpp"

std::any Interpreter::interpret(const std::unique_ptr<Expression::IExpression>& expression,SourceReport::SourceReporter& reporter)
{
    try
    {
        return expression->accept(*this);
    }
    catch(TypeError& error)
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(error.token.lineNumber),error.errorMessage());
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        return nullptr;
    }
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
