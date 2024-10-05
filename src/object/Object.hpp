#pragma once

#include "string"
#include "any"

namespace Object
{
    std::string toString(const std::any& value);
    template<typename T, typename... Args>
    bool typeChecker(Args... args) {
        return (... && (args.has_value() && args.type() == typeid(T)));
    }
}
