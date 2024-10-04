#include <any>
#include <string>

namespace GenericType
{
    std::string toString(const std::any& value) {
        if (!value.has_value()) {
            return std::string("null");
        }
        if (value.type() == typeid(int)) {
            return std::to_string(std::any_cast<int>(value));
        }
        if (value.type() == typeid(double)) {
            return std::to_string(std::any_cast<double>(value));
        }
        if (value.type() == typeid(std::string)) {
            return std::any_cast<std::string>(value);
        }
        if (value.type() == typeid(float)) {
            return std::to_string(std::any_cast<float>(value));
        }
        return "Unsupported type";
    }

}
